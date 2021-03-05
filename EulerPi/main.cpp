#include <iostream>
#include "PiApproximation.h"

int main() {
	using namespace std;
	constexpr uint32_t terms = 8;
	cout.precision(terms);
	cout << "Pi = " << CppSample::piApproximation(terms) << endl;
	return 0;
}