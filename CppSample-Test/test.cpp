#include "pch.h"
#include "BitParity/Parity.h"

TEST(BitPuzzleTest, ParityCheck) {
	using namespace std;
	auto [oddParity, setBits] = CppSample::parity(0x97);
	EXPECT_TRUE(oddParity);
	//Show set bits
	for_each(setBits.cbegin(), setBits.cend(), [](auto item) { cout << hex <<"0x"<<setfill('0')<<setw(2)<< item << ","; });
	cout << endl;
	auto [parity, bits] = CppSample::parity(0xFF);
	EXPECT_FALSE(parity);
}