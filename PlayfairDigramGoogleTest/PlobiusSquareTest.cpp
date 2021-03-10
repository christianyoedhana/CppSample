#include <string>
#include <utility>
#include <array>
#include "pch.h"
#include "PlayfairDigram\PlobiusSquare.h"

using playfair_digram::PlobiusSquare;
using std::string;
using std::pair;
using std::array;

//TEST CRITERIA
//COMPILE TIME
//PlobiusSquare cipher; //GENERATES COMPILE ERROR
//void foo(const PlobiusSquare& sq); foo("ABCDE"); //IMPLICIT CONVERSION COMPILE ERROR
//auto cipherMoved = std::move<PlobiusSquare>(cipher); //MUST COMPILE
//cipher.letter(0,0); must throw a std::exception for accessing an empty array
//cipher.content(); must throw an exception.
//cipher.coordinate('A') must throw a std::exception for accessing an empty unordered_map

//RUNTIME
//CAPITALIZATION TEST
//PlobiusSquare chiper("abcdefghijklmnopqrstuvwxyz").content() == std::string{"ABCDEFGHI/JKLMNOPQRSTUVWXYZ"};
//PlobiusSquare chiper("abcdefghijklmnopqrstuvwxyz").content() != std::string{"abcdefghi/jklmnopqrstuvwxyz"};
//PlobiusSquare chiper{"python"};
//cipher.content() == {"PYTHONABCDEFGI/JKLMQRSUVWXZ"};

TEST(PlobiusSquareTest, ContentTest) {
	PlobiusSquare square1{ "abcdefghijklmnopqrstuvwxyz" };
	string rep = square1.content();
	EXPECT_EQ(rep, string{ "ABCDEFGHI/JKLMNOPQRSTUVWXYZ" });
	PlobiusSquare square2{ "abcdefghi/jklmnopqrstuvwxyz" };
	rep = square2.content();
	EXPECT_NE(rep, string{ "abcdefghi/jklmnopqrstuvwxyz" });
	PlobiusSquare cipher{ "python" };
	rep = cipher.content();
	EXPECT_EQ(rep,string{"PYTHONABCDEFGI/JKLMQRSUVWXZ"});
}

TEST(PlobiusSquareTest, AccessValidationTest)
{
	PlobiusSquare cipher{ "playfair" };
	try {
		cipher.coordinate('P');	//must not throw an exception
	}
	catch (const PlobiusSquare::EncryptionError&)
	{
		EXPECT_TRUE(false);
	}

	try {
		cipher.coordinate('p');
	}
	catch (const PlobiusSquare::EncryptionError&)
	{
		EXPECT_TRUE(true);
		return;
	}
	EXPECT_TRUE(false);
}

TEST(PlobiusSquareTest, AccessTest) {
	PlobiusSquare cipher{ "playfairexample" };
	string rep = cipher.content();
	EXPECT_EQ(rep, string{"PLAYFI/JREXMBCDGHKNOQSTUVWZ"});
	PlobiusSquare::Coordinate coord1 = cipher.coordinate('I');
	PlobiusSquare::Coordinate coord2 = cipher.coordinate('J');
	EXPECT_EQ(coord1, coord2);
	const string testContent{ "PLAYFIREXMBCDGHKNOQSTUVWZ" };	//letter J is implicitly paired with letter I. So the table omits storing J
	
	using ChiperTable = array<array<char, cipher.dim()>, cipher.dim()>;
	/*const ChiperTable cipherTable{{{'P','L','A','Y','F'},
								{'I','R','E','X','M'},
								{'B','C','D','G','H'},
								{'K','N','O','Q','S'},
								{'T','U','V','W','Z'}}};*/
	string::size_type index = 0;
	for (ChiperTable::size_type row = 0; row < cipher.dim(); ++row){
		for (ChiperTable::size_type col = 0; col < cipher.dim(); ++col, ++index) {
			EXPECT_TRUE(cipher[row][col] == testContent[index]);
			EXPECT_EQ(cipher.coordinate(testContent[index]), PlobiusSquare::Coordinate(row, col));
		}
	}	
}