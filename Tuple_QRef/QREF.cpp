#include <tuple>
#include <string>
#include <iostream>

//I agree that this statement should never appear in a header file to prevent accidental namespace inclusion.
//In a cpp file, however, I cannot agree on the reasons not to do this just for the standard library namespace.
//This is a convenient shorthand, scoped limited to only this compilation unit. YOU should be the one guarding against name collision with STL.
//not the other way round. STL forms C++. If you have a function sqrt, you should scope it in your own namespace.
//Any unscoped sqrt must be treated like a C++ keyword, i.e the language library definition of sqrt is the one at play.
using namespace std;

//Sample function to return a string, an int, and a bool
tuple<string, int, bool> ifTrueConsumeTheRest(bool consume) noexcept {
	return consume ? make_tuple("Eat This!", 47, consume) : make_tuple("Meh", -1, consume);
}

struct Consumer {
	string m_say;
	int m_howMany = 0;
};

void QREF() {
	Consumer consumer;
	bool isUseful = false;

	//std::tie returns a tuple of references. Assign this l-value to the return r-value and create a side-effect on the mapped variable.
	tie(consumer.m_say, consumer.m_howMany, isUseful) = ifTrueConsumeTheRest(true);
	//structured binding since C++ 17. Can be used only on previously undeclared entities.
	auto [meh, dontCare, useless] = ifTrueConsumeTheRest(false);

	cout << meh << " " << dontCare << " " << boolalpha << useless << endl;
}