A template parameter pack is a template parameter that accepts zero or more template arguments (non-types, types, or templates). To read more about parameter pack, click here.

Create a template function named reversed_binary_value. It must take an arbitrary number of bool values as template parameters. These booleans represent binary digits in reverse order. Your function must return an integer corresponding to the binary value of the digits represented by the booleans. For example: reversed_binary_value<0,0,1>() should return .

Input Format

The first line contains an integer, t , the number of test cases. Each of the  subsequent lines contains a test case. A test case is described as 2 space-separated integers,  and , respectively.

x is the value to compare against.
y represents the range to compare: 64*y to 64*y+63 to .
Constraints

The number of template parameters passed to reversed_binary_value will be .
Output Format

Each line of output contains  binary characters (i.e., 's and 's). Each character represents one value in the range. The first character corresponds to the first value in the range. The last character corresponds to the last value in the range. The character is  if the value in the range matches ; otherwise, the character is .

Sample Input

2
65 1
10 0
Sample Output

0100000000000000000000000000000000000000000000000000000000000000
0000000000100000000000000000000000000000000000000000000000000000
Explanation

The second character on the first line is a 1 , because the second value in the range  64-127 is 65 and x is 11.

The eleventh character on the second line is a 1, because the eleventh value in the range 0-63 is 10 and x is 10.

All other characters are zero, because the corresponding values in the range do not match .