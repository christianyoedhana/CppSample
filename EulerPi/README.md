Key concept: C++ threading, cout formatting

This is an approximation to PI attributed to Euler.
The formula is as follows: (PI^2)/6 =  1 + 1/4 + 1/9 + 1/16 + ... + 1/(n^2)
I use this as a multi-threadin exercise, because the series is a natural SIMD problem:
1. Each terms is independent.
2. 1 instruction with n natural numbers from 1 to n forms the solution

The solution needs only 1 shared variable to store the sum of the terms. Just remember to format the output to as many decimal places as possible.
n threads returning 1/(n^2) and adding to the shared variable should be enough to compute the PI approximation

Solution, however, is not the same as the PI constant in the STL. Some of the terms is different.