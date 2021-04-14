#include "Parity.h"

namespace CppSample {
	std::tuple<bool, std::vector<unsigned int>> parity(unsigned int number) {
		unsigned int numSetBit = 0;
		std::vector<unsigned int> setBits;
		while (number) {
			auto setbit = number & ~(number - 1);
			number = number ^ setbit;
			numSetBit += 1;
			setBits.push_back(setbit);
		}
		//implicit conversion of 0 to false and 1 to true
		return std::make_tuple(numSetBit % 2 > 0, setBits);
	}
}