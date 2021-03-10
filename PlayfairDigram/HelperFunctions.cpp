#include "HelperFunctions.h"
#include <string>
#include <iostream>
#include <array>

using std::string;
using std::vector;
using std::cerr;
using std::array;
using std::make_pair;

namespace playfair_digram {
	InvalidKeyException::InvalidKeyException(const std::string& errMsg) {
		cerr << errMsg << std::endl;
	}
	const string whitespaces = { " \t\f\v\n\r" };

	bool validateMessage(const string& message) {
		const string valid = { " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
		return (message.size() > 0) && (message.find_first_not_of(valid) == string::npos) && (message.find_first_not_of(whitespaces) != string::npos);
	}

	//Remove all spaces from input and return the resulting string. Can be an empty string
	string removeSpaces(const string& input) {
		string output(input);
		//remove all leading whitespaces
		//string::size_type pos = output.find_first_not_of(whitespaces);
		//if (pos == string::npos) return "";	//input contains only whitespaces
		//if (pos > 0) output.erase(0, pos - 1);
		//remove all trailing whitespaces
		//pos = output.find_last_not_of(whitespaces);
		//if (pos != string::npos) output.erase(pos + 1);
		string::size_type pos = 0;
		//This is just an exercise in using find_first_of and find_first_not_of. In terms of removing spaces, this is very inefficient
		while ((pos = output.find_first_of(whitespaces, pos)) != string::npos) {
			string::size_type past = output.find_first_not_of(whitespaces, pos);
			if (past != string::npos) {
				output.erase(pos, past - pos);
			}
			else {//erase trailing whitespace
				output.erase(pos);
			}
		}
		return output;
	}

	vector<string> applyRule1(const string& message) {
		//remove all leading whitespaces
		string toTransform(message);
		string::size_type pos = toTransform.find_first_not_of(whitespaces);
		if (pos == string::npos) throw InvalidKeyException("Invalid message " + message);
		if (pos > 0) toTransform.erase(0, pos-1);
		//remove all trailing whitespaces
		pos = toTransform.find_last_not_of(whitespaces);
		if (pos != string::npos) toTransform.erase(pos + 1);
		//now transform
		vector<string> transformed;
		string digram;
		for (auto letter : toTransform){
			if (whitespaces.find(letter) != string::npos) continue;
			//add character or split?
			letter = std::toupper(letter);
			if (digram.find(letter) != string::npos) {
				digram.push_back('X');
				transformed.push_back(digram);
				digram.clear();
			}
			digram.push_back(letter);
			if (digram.size() == 2) {
				transformed.push_back(digram);
				digram.clear();
			}
		}
		//push last digram, if applicable
		if (!digram.empty()) {
			digram.push_back('X');
			transformed.push_back(digram);
		}
		return transformed;
	}

	template<typename Predicate> bool checkRule(const string& digram, const PlobiusSquare& table, const Predicate& rule) {
		array<PlobiusSquare::Coordinate, 2> pos;
		pos[0] = table.coordinate(digram[0]);
		pos[1] = table.coordinate(digram[1]);
		return rule(pos);
	}

	bool isRule2(const string& digram, const PlobiusSquare& table) {
		return checkRule(digram, table, [](const array<PlobiusSquare::Coordinate, 2>& pos) {return pos[0].first == pos[1].first; });
	}

	//Operation type is meant to be an Encrypt or Decrypt functors.
	//Op determines whether the resulting coordinate is 1 to the right or left of the letters in the input digram
	template<typename Operation> string rule2_3op (const string& digram, const PlobiusSquare& table, const Operation& op) {
		string output;
		for (auto letter : digram) {
			PlobiusSquare::Coordinate pos = op(table.coordinate(letter));
			output.push_back(table[pos.first][pos.second]);
		}
		return output;
	}

	string encryptRule2(const string& digram, const PlobiusSquare& table) {
		return rule2_3op(digram, table, [&](const PlobiusSquare::Coordinate& pos) {return make_pair(pos.first, (pos.second + 1) % table.dim()); });
		//This is where PlobiusSquare::Coordinate's ugliness surfaces
		//I am not tolerating the ugliness of PlobiusSquare::Coordinate here. The type needs its own interface to decouple it from std::pair
	}

	string decryptRule2(const string& digram, const PlobiusSquare& table) {
		return rule2_3op(digram, table, [&](const PlobiusSquare::Coordinate& pos) {return make_pair(pos.first, (pos.second + table.dim() - 1) % table.dim()); });
	}

	bool isRule3(const string& digram, const PlobiusSquare& table) {
		return checkRule(digram, table, [](const array<PlobiusSquare::Coordinate, 2>& pos) { return pos[0].second == pos[1].second; });
	}

	string encryptRule3(const string& digram, const PlobiusSquare& table) {
		return rule2_3op(digram, table, [&](const PlobiusSquare::Coordinate& pos) {return make_pair((pos.first + 1) % table.dim(), pos.second); });
	}

	string decryptRule3(const string& digram, const PlobiusSquare& table) {
		return rule2_3op(digram, table, [&](const PlobiusSquare::Coordinate& pos) {return make_pair((pos.first + table.dim() - 1) % table.dim(), pos.second); });
	}

	bool isRule4(const string& digram, const PlobiusSquare& table) {
		return checkRule(digram, table, [](const array<PlobiusSquare::Coordinate, 2>& pos) { return ((pos[0].second != pos[1].second) && (pos[0].first != pos[1].first)); });
	}

	string encryptDecryptRule4(const string& digram, const PlobiusSquare& table) {
		string output;
		array<PlobiusSquare::Coordinate, 2> pos;
		pos[0] = table.coordinate(digram[0]);
		pos[1] = table.coordinate(digram[1]);
		output.push_back(table[pos[0].first][pos[1].second]);
		output.push_back(table[pos[1].first][pos[0].second]);
		return output;
	}

	string encryptRule4(const string& digram, const PlobiusSquare& table) {
		return encryptDecryptRule4(digram, table);
	}

	//I think encrypt and decrypt of rule 4 is the same operation
	string decryptRule4(const string& digram, const PlobiusSquare& table) {
		return encryptDecryptRule4(digram, table);
	}
}