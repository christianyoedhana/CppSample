Key concept: C++ threading, cout formatting, lambda, generic programming using C++ templates

This sample contains 3 series that approximates PI
Euler: (PI^2)/6 =  1 + 1/4 + 1/9 + 1/16 + ... + 1/(n^2)
Gregory-Leibnitz: PI = 4 - 4/3 + 4/5 - 4/7 + ... + 4/(2n-1)
Nilakantha: PI = 3 + 4/ (2x3x4) + 4/(4x5x6) + ... + 4/(2n x (2n+1) x (2n+2))

I use this as a multi-threadin exercise, because the series is a natural SIMD problem:
1. Each terms is independent.
2. 1 instruction with n natural numbers from 1 to n forms the solution

No shared variable needed, so std::async is suitable for creating the future that holds the result of each terms in the series.
If I sum the terms inside the term's function, I will stall the threads unnecessarily.