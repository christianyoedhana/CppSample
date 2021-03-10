#include <iostream>
#include <string>
#include <array>
#include <unordered_map>
#include <locale>
#include "PlobiusSquare.h"

using std::string;
using std::array;
using std::unordered_map;
using std::cerr;

namespace playfair_digram {
	PlobiusSquare::EncryptionError::EncryptionError (const string& message){
		cerr << message << std::endl;
	}

	PlobiusSquare::PlobiusSquare(const string& keyword) { //: m_table{m_dim * m_dim}
		populateTable(keyword);
	}

	/// <summary>
	/// populateTable inserts all unique entries from key, then the rest of the uninserted alphabet
	/// </summary>
	void PlobiusSquare::populateTable(const string& key) {
		const string cipherKeys = key + string{ "ABCDEFGHIKLMNOPQRSTUVWXYZ" };
		auto keyIter = cipherKeys.begin();
		for (Row::size_type row = 0; row < m_index.size(); ++row) {
			for (Row::size_type col = 0; col < m_index[row].size(); ++col) {
				while (keyIter != cipherKeys.end()) {
					char upperLetter = std::toupper(*(keyIter++));
					if (upperLetter == 'J') upperLetter = 'I';
					//If we find a unique letter
					if (m_table.find(upperLetter) == m_table.end()) {
						m_index[row][col] = upperLetter;
						m_table.insert(std::make_pair(upperLetter, PlobiusSquare::Coordinate{ row,col }));
						break;	//increment column, and if necessary, row
					}
				}
			}
		}
	}

	PlobiusSquare::Coordinate PlobiusSquare::coordinate(char letter) const {
		if (letter == 'J') letter = 'I';
		const auto result = m_table.find(letter);
		if (result == m_table.end()) {
			throw EncryptionError{ "Cannot find " + letter};
		}
		return (*result).second;
	}

	const PlobiusSquare::Row& PlobiusSquare::operator[](Row::size_type row) const{
		return m_index[row];	//Rely on std::array index out of range exception thrown by m_index
	}

	string PlobiusSquare::content() const {	//I and J will show up as I/J. PlayfairDigram is expected to use coordinate() and letter(), not content().
		string squareContent;
		for (Row::size_type row = 0; row < m_index.size(); ++row) {
			for (Row::size_type col = 0; col < m_index[row].size(); ++col) {
				if (m_index[row][col] == 'I') {
					squareContent += "I/J";
				}
				else {
					squareContent += m_index[row][col];
				}
			}
		}
		return squareContent;
	}
}