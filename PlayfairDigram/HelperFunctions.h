#pragma once
#include <string>
#include <vector>
#include "PlobiusSquare.h"

namespace playfair_digram {
	class InvalidKeyException {
	public:
		explicit InvalidKeyException(const std::string& errMsg);
	};

	//Input validator. Message to encode cannot contain non-alphanumeric or whitespace. Must accept both lower case and uppercase alphabet
	//Also do not accept all whitespace message
	bool validateMessage(const std::string& message);
	
	//Remove all spaces from input and return the resulting string. Can be an empty string
	std::string removeSpaces(const std::string& input);

	//Rule #1. Take a digram and break it up as necessary. If input digram got split, return a vector of the split digrams. Otherwise return an empty vector.
	//Break up the message into capital-letter, no white space, digram string. Each digram string contains 2 letters
	//Assumes that message is a valid message.
	//Uses the letter 'X' for splitting repeating letters and padding single letters
	std::vector<std::string> applyRule1(const std::string& message);
	
	//Rule 2,3, and 4 expects a well-formed digram. No checking will be performed
	//Rule #2. Find the nearest, wrap-around right neighbor if the letters in the digram are on the same row
	bool isRule2(const std::string& digram, const PlobiusSquare& table);
	std::string encryptRule2(const std::string& digram, const PlobiusSquare& table);
	std::string decryptRule2(const std::string& digram, const PlobiusSquare& table);

	//Rule #3 Find the nearest, wrap-around neighbor below if digram letters are on the same colums
	bool isRule3(const std::string& digram, const PlobiusSquare& table);
	std::string encryptRule3(const std::string& digram, const PlobiusSquare& table);
	std::string decryptRule3(const std::string& digram, const PlobiusSquare& table);

	//Rule #4 Find the vertices if digram letters form a rectable in the table
	bool isRule4(const std::string& digram, const PlobiusSquare& table);
	std::string encryptRule4(const std::string& digram, const PlobiusSquare& table);
	std::string decryptRule4(const std::string& digram, const PlobiusSquare& table);

	//@todo to reduce table access, implement this
	//template<typename Pred, typename Rule> std::string encode(const std::array<PlobiusSquare::Coordinate, 2>& coords, Pred ruleCondition, Rule action);
	//Pred will be disposed by a function, or hand coded using a lambda expression. Same as rule
}