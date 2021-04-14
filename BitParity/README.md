Determining which bits and parity of a bit pattern seems like a popular interview question. I know I flunked mine in 2001 during my
Microsoft interview. And the trick is simple, using x & ~(x-1) = the set bit. Then repeatedly doing x = (the set bit) XOR x until x=0, and counting
the number of times this is done gives you the number of set bit. When dealing with a large number, you can break it up into byte chunks, then 
either calculate the number of set bit, or use a lookup table. so do a series of x = (x >> 8) & (unsigned int) 0x11 until x = 0; When returning
which bits are set, don't forget to do << 8 n number of times it takes to do >> 8.