#include <vector>
#include <future>
#include "PiApproximation.h"
#include "SutterMonitor/SutterMonitor.h"

namespace CppSample {

	double oneOverISquare(double i) {
		return 1 / pow(i, 2);
	}

	double piApproximation(std::uint32_t numTerms) {
		using namespace std;
		vector<future<double>> series;
		for (decltype(numTerms) term = 1; term < numTerms + 1; ++term) {
			series.push_back(async(launch::async, [=]() { return 1.0 / pow(term, 2); }));
		}

		double sum = 0;
		//Wait for all terms to complete
		for_each(series.begin(), series.end(), [&sum](auto& fut) { sum += fut.get(); });
		//sum = pi^/6
		return sqrt( 6 * sum);
	}

}