#pragma once
#include <future>
#include <vector>
#include <algorithm>

namespace CppSample {
//Follow Bjarne's advice when designing a templated class: develop the non-templated version first, then templatize the final class. Eventually I will allow 
//other series as a policy for this class
//A caution about std::async: Seems like async is intended for independent threads. The PCL cautions against using thread functions using shared variables launched by
//std::async.
//Sample use case:
//auto leibnitz = [](uint32_t i) { return pow(-1, i) * 4/ (2*i - 1) ; }
//auto pi = piApprox(1000, leibnits, [](auto summ){ return sum;});
//
//Calculate PI directly using series summation. Final allows you to modify the sum of the terms for the final pi approximation
template <typename Term, typename Final>
double piApprox(uint32_t nth, Term term, Final final) {
	std::vector<std::future<double>> series;
	for (decltype(nth) n = 1; n < nth + 1; ++n) {
		series.push_back(async(std::launch::async, term, n));
	}
	
	double sum = 0;
	std::for_each(series.begin(), series.end(), [&sum](auto& fut) { sum += fut.get(); });
	return final(sum);
}
}


