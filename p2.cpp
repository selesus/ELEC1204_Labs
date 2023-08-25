#include <iostream>
#include "p2.h"

// Logical Functions

bool logicalAnd(bool in1, bool in2)
{
    return in1 && in2;
}

bool logicalOr(bool in1, bool in2)
{
    return in1 || in2;
}
bool logicalXor(bool in1, bool in2)
{
    return in1 != in2;
}

// Single Bit Adder

adderOutput singleAdder(bool in1, bool in2, bool cin)
{
    adderOutput returnStruct;
    
    returnStruct.carryOutput = logicalOr( logicalAnd(cin,logicalXor(in1, in2) ), logicalAnd(in1, in2) );
    returnStruct.sum = logicalXor(cin, logicalXor(in1, in2) );

    return returnStruct;
}

int main(void)
{

    return 0;
}