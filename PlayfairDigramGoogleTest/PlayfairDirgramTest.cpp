#include <string>
#include <vector>
#include <iostream>
#include "pch.h"
#include "PlayfairDigram/PlobiusSquare.h"
#include "PlayfairDigram/HelperFunctions.h"
#include "PlayfairDigram/PlayfairDigram.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using playfair_digram::validateMessage;
using playfair_digram::removeSpaces;
using playfair_digram::applyRule1;
using playfair_digram::isRule2;
using playfair_digram::encryptRule2;
using playfair_digram::PlayfairDigram;

TEST(PlayfairDigramTest, ValidateMessageTest) {
	//@todo expand the list
	const vector<string> invalidMessages = { {""},  {"AA1"}, {"ABC@"}, {"A %"}, {"  !"}, {" \t\f\v\n\r"} };
	for (const auto& msg : invalidMessages) {
		EXPECT_FALSE(validateMessage(msg));
	}
	
	//@todo expand the list
	const vector<string> validMessages = { {"ABC"}, {" a A B "},  {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"} };
	for (const auto& msg : validMessages) {
		EXPECT_TRUE(validateMessage(msg));
	}
}

TEST(PlayfairDigramTest, RemoveAllSpacesTest) {
	const string input = { "   A B C D EFGH IJK    " };
	const string output = { "ABCDEFGHIJK" };
	EXPECT_EQ(removeSpaces(input), output);
}

TEST(PlayfairDigramTest, Rule1Test)
{
	const vector<string> messages = { {"A"}, {"  AbCdE FGHI JKLM  "}, {"aABCCcD"} };
	const vector<vector<string>> expectedDigrams = { {"AX"}, { {"AB"}, {"CD"}, {"EF"}, {"GH"}, {"IJ"}, {"KL"}, {"MX"} },
													{{"AX"}, {"AB"}, {"CX"}, {"CX"}, {"CD"}} };
	for (vector<string>::size_type index = 0; index < messages.size(); ++index ) {
		const vector<string> digram = applyRule1(messages[index]);
		EXPECT_EQ(digram, expectedDigrams[index]);
	}
}

TEST(PlayfairDigramTest, RuleTest2)
{
	//This is how the table look like
	/*const ChiperTable cipherTable{{{'P','L','A','Y','F'},
									 {'I','R','E','X','M'},
									 {'B','C','D','G','H'},
									 {'K','N','O','Q','S'},
									 {'T','U','V','W','Z'}}};*/
	playfair_digram::PlobiusSquare table{ "playfairexample" };
	EXPECT_FALSE(isRule2("PI", table));
	EXPECT_FALSE(isRule2("PZ", table));
	EXPECT_TRUE(isRule2("NS", table));
	EXPECT_TRUE(isRule2("IJ", table));
	EXPECT_EQ(encryptRule2("IJ", table), "RR");
	EXPECT_EQ(decryptRule2("RR", table), "II");	//This is the weakness of the 5x5 plobius square. It works for greek alpha, not for latin
	EXPECT_EQ(encryptRule2("XX", table), "MM");
	EXPECT_EQ(decryptRule2("MM", table), "XX");
	EXPECT_EQ(encryptRule2("NS", table), "OK");
	EXPECT_EQ(decryptRule2("OK", table), "NS");
	EXPECT_EQ(encryptRule2("TZ", table), "UT");
	EXPECT_EQ(decryptRule2("UT", table), "TZ");
}

TEST(PlayfairDigramTest, RuleTest3) {
	playfair_digram::PlobiusSquare table{ "playfairexample" };
	EXPECT_TRUE(isRule3("PI", table));
	EXPECT_TRUE(isRule3("FZ", table));
	EXPECT_FALSE(isRule3("NS", table));
	EXPECT_FALSE(isRule3("LZ", table));
	EXPECT_TRUE(isRule3("IJ", table));
	EXPECT_EQ(encryptRule3("IJ", table), "BB");
	EXPECT_EQ(decryptRule3("BB", table), "II");
	EXPECT_EQ(encryptRule3("XX", table), "GG");
	EXPECT_EQ(decryptRule3("GG", table), "XX");
	EXPECT_EQ(encryptRule3("VA", table), "AE");
	EXPECT_EQ(decryptRule3("AE", table), "VA");
	EXPECT_EQ(encryptRule3("MS", table), "HZ");
	EXPECT_EQ(decryptRule3("HZ", table), "MS");
}

TEST(PlayfairDigramTest, RulTest4) {
	playfair_digram::PlobiusSquare table{ "playfairexample" };
	EXPECT_TRUE(isRule4("RQ", table));
	EXPECT_TRUE(isRule4("SX", table));
	EXPECT_FALSE(isRule4("KO", table));
	EXPECT_FALSE(isRule4("NR", table));
	EXPECT_FALSE(isRule4("IJ", table));
	EXPECT_EQ(encryptRule4("QR", table), "NX");
	EXPECT_EQ(encryptRule4("PZ", table), "FT");
	EXPECT_EQ(encryptRule4("ZP", table), "TF");
	EXPECT_EQ(encryptRule4("GE", table), "DX");
	
	EXPECT_EQ(decryptRule4("NX", table), "QR");
	EXPECT_EQ(decryptRule4("FT", table), "PZ");
	EXPECT_EQ(decryptRule4("TF", table), "ZP");
	EXPECT_EQ(decryptRule4("DX", table), "GE");
}

TEST(PlayfairDigramTest, EncrypTest) {
	PlayfairDigram cipher("playfairexample");
	string encoded = { "BMODZBXDNABEKUDMUIXMMOUVIF" };
	EXPECT_EQ(cipher.encrypt("Hide the gold in the tree stump"), encoded);
}

TEST(PlayfairDigramTest, DecrypTest) {
	PlayfairDigram cipher("playfairexample");
	const string encoded = { "BMODZBXDNABEKUDMUIXMMOUVIF" };
	const string decoded = { "HIDETHEGOLDINTHETREXESTUMP" };
	EXPECT_EQ(cipher.decrypt(encoded), decoded);
}