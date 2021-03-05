#include <iostream>
#include "PiApproximation.h"

int main() {
	using namespace std;
	constexpr uint32_t terms = 20;
	cout << "Comparing PI convergence after " << terms << " terms" << endl;
	cout.precision(terms);

	auto euler = [](uint32_t n) { return 1.0 / (1.0 * n * n); };
	cout << "Euler Pi = " << CppSample::piApprox(terms, euler, [](auto sum) { return sqrt(6.0 * sum); }) << endl;

	//leibnitz approximation is a direct summation of the terms to produce pi, so Final is a simple passthrough lambda
	auto leibnitz = [](uint32_t n) { return pow(-1, n-1) * 4 / (2.0 * n - 1); };
	cout << "Leibnitz Pi = " << CppSample::piApprox(terms, leibnitz, [](auto sum) { return sum; }) << endl;

	auto nilakantha = [](uint32_t n) { double n2 = 2.0 * n; return pow(-1, n - 1) * 4 / (n2 * (n2 + 1.0) * (n2 + 2.0)); };
	cout << "Nilakantha Pi = " << CppSample::piApprox(terms, nilakantha, [](double sum) { return 3 + sum; }) << endl;
	return 0;
}