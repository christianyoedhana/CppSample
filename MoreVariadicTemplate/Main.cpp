/**
* I have no friggin clue what this program is trying to achieve. I have a requirement and I have the solution.
* This looks like an excellent excercise in template variadics. So far my encounters with template variadics have been with the typed template
* variadic parameter.
* This example is using a non-typed, and it confuses the heck out of me. The code works, but I need an explanation here. Maybe Bjarne's book has the explanation.
**/
#include <iostream>
using namespace std;

template<bool digit> int reversed_binary_value_helper(int pow) {
    return (digit ? 1 : 0) * pow;
}

//This template parameter list generaters C2668.
//template <bool first, bool... digits>
//While this one resolves in the compiler just fine. Why?
//Maybe the next non-type template parameter is necessary because I don't have a template specialization with no template parameter? Nope.
//That's template specialization! Different semantics
template<bool first, bool second, bool... digits>
int reversed_binary_value_helper(int pow) {
    return pow * first + reversed_binary_value_helper<second, digits...>(pow << 1);
}

template<bool... digits>
int reversed_binary_value() {
    return reversed_binary_value_helper<digits...>(1);
}

template <int n, bool...digits>
struct CheckValues {
    static void check(int x, int y)
    {
        CheckValues<n - 1, 0, digits...>::check(x, y);
        CheckValues<n - 1, 1, digits...>::check(x, y);
    }
};

template <bool...digits>
struct CheckValues<0, digits...> {
    static void check(int x, int y)
    {
        int z = reversed_binary_value<digits...>();
        std::cout << (z + 64 * y == x);
    }
};

int main()
{
    int t; std::cin >> t;

    for (int i = 0; i != t; ++i) {
        int x, y;
        cin >> x >> y;
        CheckValues<6>::check(x, y);
        cout << "\n";
    }
}
