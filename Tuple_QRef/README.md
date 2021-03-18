This project is my Quick Reference guide to creating, accessing, and mapping std::tuple and its members.
Why std::tuple?
I use this to return multiple return values from a function. Before std::tuple, some of the available options are:
1. std::pair. As its name suggests, you can return up to 2 values from the return statement.
2. Struct reference in the function parameter. This is still one of my recommended method, and std::tuple competes favorably with this technique. I also promote using a const ref struct to pass in multiple input parameters for code readability. If you need examples on functions with numerous (think more than 5) parameters, look at Win32 functions. I think using structs instead of long parameter lists make the function prototype more readable, thus improving code readability.
3. And of course the good, old, type reference (and its pointer equivalent) parameter.

In C++ 17, we can conveniently map (bind?) std::tuple members to struct instance members, or local variables, using std::tie. Unfortunately, I keep forgetting the syntax.
There are plenty of reference material in stackoverflow for this. Many times I found reading stackoverflow threads as TMI.
So I make this QRef to summarize what I really want to remember about std::tuple and its uses. The QRef will grow with the scope of my uses cases.

I hope you find this QREF useful.

BTW pilots love QREF!
