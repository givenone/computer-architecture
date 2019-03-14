//--------------------------------------------------------------
// 
//  4190.308 Computer Architecture (Fall 2018)
//
//  Project #1: 64-bit Arithmetic using 32-bit integers
//
//  September 18, 2018
//
//  Jin-Soo Kim (jinsoo.kim@snu.ac.kr)
//  Systems Software & Architecture Laboratory
//  Dept. of Computer Science and Engineering
//  Seoul National University
//
//--------------------------------------------------------------

#include <stdio.h>
#include "pa1.h"

// NOTE!!!!!
// You should use only 32-bit integer operations inside Uadd64(), Usub64(), 
// and Umul64() functions. 


// Uadd64() implements the addition of two 64-bit unsigned integers.
// Assume that A and B are the 64-bit unsigned integer represented by
// a and b, respectively. In the following example, x.hi and x.lo should
// have the upper and lower 32 bits of (A + B), respectively.

HL64 Uadd64 (HL64 a, HL64 b)
{
	HL64 	x;
	x.lo = a.lo + b.lo;
    x.hi = (x.lo >= a.lo) && (x.lo >= b.lo) ? a.hi + b.hi : a.hi + b.hi + 1U;
	return x;
}

// Usub64() implements the subtraction between two 64-bit unsigned integers.
// Assume that A and B are the 64-bit unsigned integer represented by
// a and b, respectively. In the following example, x.hi and x.lo should
// have the upper and lower 32 bits of (A - B), respectively.

HL64 Usub64 (HL64 a, HL64 b)
{
	HL64 	x;
	x.lo = a.lo - b.lo;
    x.hi = (a.lo >= b.lo) ? a.hi - b.hi : a.hi - 1U - b.hi;
	return x;
}

// Usub64() implements the multiplication of two 64-bit unsigned integers.
// Assume that a' and b' are the 64-bit unsigned integer represented by
// a and b, respectively.  In the following example, x.hi and x.lo should
// have the upper and lower 32 bits of (A * B), respectively.

HL64 Umul64 (HL64 a, HL64 b)
{
	HL64 	x, y, z;
	unsigned int sig = 1<<16;

    y.lo = (a.lo % sig) * (b.lo % sig);
    y.hi = 0;

    u32 temp = (a.lo % sig) * (b.lo / sig);
    z.hi = temp / sig;
    z.lo = (temp % sig) << 16;

    y = Uadd64(y,z);

    temp = (b.lo % sig) * (a.lo / sig);
    z.hi = temp / sig;
    z.lo = (temp % sig) << 16;

    y = Uadd64(y,z);

    x.lo = a.lo * b.lo;
    x.hi = a.hi * b.lo + a.lo * b.hi
           + (a.lo / sig) * (b.lo / sig) + y.hi;

	return x;
}




