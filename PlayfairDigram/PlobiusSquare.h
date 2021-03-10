#pragma once
#include <memory>
#include <string>
#include <array>
#include <unordered_map>

namespace playfair_digram
{
	//Typical Latin-alphabet 5x5 Plobius Square, with I and J occupying the same space.
	//Contains capitalized letters only. 
	class PlobiusSquare {
		static const unsigned int m_dim = 5;

	public:
		using Coordinate = std::pair<size_t, size_t>;
		PlobiusSquare() = delete;
		//Keyword accepts upper case and lower case sentences with whitespaces.
		//The user of the square is responsible for excluding unacceptable characters from they keyword
		explicit PlobiusSquare(const std::string& keyword);
		//Find the coordinates of a given letter. If the letter is in the table, return the [row,col]. Otherwise throw PlobiusSquare::LetterNotFound. 
		//This is an indication that either the input is invalid, or the table is malformed
		Coordinate coordinate(char letter) const;
		//char letter(unsigned int row, unsigned int col) const;
		using Row = std::array<char, m_dim>;
		const Row& operator[](Row::size_type row) const;
		//and just to play with constexpr. The inline and const explicitly request the behavior, given how implicit constexpr behaviour will differ between c++14 and c++20
		//Maybe this function should be a static function
		inline constexpr unsigned int dim() const { return m_dim; }	//always returns 5
		std::string content() const;	//I and J will show up as I/J. PlayfairDigram is expected to use coordinate() and letter(), not content().

		class EncryptionError {
		public:
			explicit EncryptionError(const std::string& message);
		};

	private:
		void populateTable(const std::string& keyword);
		std::unordered_map<char, Coordinate> m_table;	//Position storage by alphabet
		std::array<std::array<char, m_dim>, m_dim> m_index;	//Letter storage by row, col
	};
}
//USE CASE:
//Auto-delete, so don't define non-virtual destructor.
//Copyable and movable, so use only copyable and movable member data type

//PlobiusSquare cipher("python);
//In the context of Playfair Chiper, to encode 'AB'
//auto loc1 = cipher.coordinate('A');
//auto loc2 = cipher.coordinate('B');
//PlayfairDigram rule #2
//if (loc1.first == loc2.first)
//{
//	code1 = cipher.letter((loc1.first + 1)%chiper.dim(), loc1.second);
//	code.push_back(code1);
//	code2 = cipher.letter((loc2.first + 1)%chiper.dim(), loc2.second);
//	code.push_back(code2);
//}
//etc...

