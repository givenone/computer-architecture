//--------------------------------------------------------------
// 
//  4190.308 Computer Architecture (Fall 2018)
//
//  Project #2: TinyFP (8-bit floating point) Representation
//
//  October 16, 2018
//
//  Jin-Soo Kim (jinsoo.kim@snu.ac.kr)
//  Systems Software & Architecture Laboratory
//  Dept. of Computer Science and Engineering
//  Seoul National University
//
//--------------------------------------------------------------

#include <stdio.h>
#include "pa2.h"

tinyfp int2tinyfp(int x)
{ // normal case
    unsigned short sign, exp, frac;
    sign = (x & 0x8000) ? 1 : 0 ;
    x = sign ? (~x + 1) : x;

    int E = 30; /// first one
    for(; E>=0; E--){
        if(x & (1<<E))
            break;
    }
    if(E == -1)
        return (sign<<7);
    exp = E + 7;
    unsigned short S = 0, R = 0, G=0;
    G = x & (E>=3 ? (1 << (E-3)) : 0);
    R = x & (E>=4 ? (1 << (E-4)) : 0); /// Round bit
    if(E>=3)
        frac = 0x7 & (x >> (E-3));
    else
        frac = 0x7 & (x << -(E-3));
    for(short start = 0; start <= E-5; start++)
        S = S || (x & 1<<start); /// Sticky bit

    (R && S) || (G && R && !S) ? frac++ : frac; // round to even

    if(frac >= 8){
        frac-=8;
        exp++;
    }
    if(exp >=15)
        return (sign << 7) | 0x78;
    else return (sign << 7) + (exp << 3) + frac;
}

int tinyfp2int(tinyfp x)
{

    int answer;
    unsigned short exp = ((x & 0x78) >> 3) ;
    short E = exp - 7; // unsigned made me debugg for 2 hours
    unsigned int frac = x & 0x07;
    if(E == 8)
        return 0x80000000;
    if(exp != 0)
        frac += 8;
    if(E<0)
        frac = frac >> (-E);
    else
        frac = frac << E;
    answer =  frac >> 3;
    return (x&0x80) ? -1 * answer : answer;
}


tinyfp float2tinyfp(float k)
{ //special
    int x = * ((int*)&k);
    unsigned int sign = (x & 0x80000000) >> 24 ;
    tinyfp answer = 0;
    int exp = ((x & 0x7f800000) >> 23) - 120 ;
    int frac = (x & 0x007fffff);
    int R = 0, S = 0, G = 0;

    if(exp >= 15){
        answer = sign | ((exp == 135 && frac) ? 0x79 : 0x78);
    }
    else if(exp <=0) {
        if (exp != -120) // 0000 case
            frac += (1 << 23);
        for (int i = 0; (i <= 19 - exp) && !S; i++)
            S = S || (frac & (1 << i));
        R = frac & (1 << (20 - exp));
        G = frac & (1 << (21 - exp));
        frac = frac >> (21 - exp);
        exp = 0;
        if ((R && S) || (G && R && !S))
            frac++;
        exp += frac/8;
        frac %=8;// overflow - exp + 1?
        answer = sign | (exp<<3) | frac;
    }
    else{
        G = frac & (1 << 20);
        R = frac & (1 << 19);
        for(int i=0; i<= 18 && !S; i++)
            S = S || (frac & (1<<i));
        frac = frac >> 20;
        if ((R && S) || (G && R && !S))
            frac++;
        exp += frac/8;
        frac %=8;
        answer = sign | (exp<<3) | frac;
    }
    return answer;
}


float tinyfp2float(tinyfp x)
{
    int exp = (x & 0x78) >> 3;
    int frac = x & 0x7;
    int answer=0;
    if(exp == 15){ // inf or nan
        answer = answer | 0x7f800000 | (frac << 20);
    }
    else if(exp == 0)
    {
        short i=1; // first nonzero
        for(; i<=3; i++){
            if((frac << i) & 8)
                break;
        }
        if(i==4)
            answer = 0;
        else{
            answer = ((121-i) << 23) | ( (frac % (1 << (3-i)) ) << (i+20));
        }
    }
    else{
        answer = ((exp+120) << 23) | (frac << 20);
    }
    answer = (x & 0x80) ? answer | (0x80000000) : answer;
    return * ((float*) &answer);
}

