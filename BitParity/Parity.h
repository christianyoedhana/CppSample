#pragma once
#include <tuple>
#include <vector>

namespace CppSample {
	//First argument returns true if number has odd parity. False if number has even parity
	//Second argument returns the set bits
	//This is useful when reading a multi-channel PCM audio header and figure out the channel mapping for PCM audio block
	std::tuple<bool, std::vector<unsigned int>> parity(unsigned int number);
}