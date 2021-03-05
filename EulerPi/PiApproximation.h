#pragma once

namespace CppSample {
//Follow Bjarne's advice when designing a templated class: develop the non-templated version first, then templatize the final class. Eventually I will allow 
//other series as a policy for this class
//Use Case:
//PiApproximation pi;
//cout<<"Pi approximation "<<pi(30)<<endl;
	double piApproximation(std::uint32_t numTerms);
/*class PiApproximation {
private:
	//Each terms will sum to a common variable. This is the variable that we are protecting
	MyPatterns::Monitor<double> m_sum;

public:
	using PiType = decltype(m_sum)::SharedData;
	//terms is the length of the series used to calculate pi. The longer the terms the more correct digits you get.
	PiType operator()(std::uint32_t terms = 20) const;

};*/
}


