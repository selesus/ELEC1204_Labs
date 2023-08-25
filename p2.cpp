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

void multiBitAdder (bool* array1, bool* array2, bool* outputArray, int arrayLength)
{
    bool carryBit = 0;
    adderOutput result;

    for (int elementNumber = 0; elementNumber < arrayLength; elementNumber++)
    {
        result = singleAdder(array1[elementNumber], array2[elementNumber], carryBit);
        outputArray[elementNumber] = result.sum;
        carryBit = result.carryOutput;
    }
}

void decimalToBinary (int inputNumber, bool* boolArray, int arrayLength)
{
    bool negativeFlag = 0;
    if (inputNumber < 0)
    {
        negativeFlag = 1;
        inputNumber = -inputNumber;
    }

    for (int elementNumber = 0; elementNumber < arrayLength; elementNumber++)
    {
        boolArray[elementNumber] = inputNumber % 2;
        inputNumber = inputNumber / 2;
    }
}

void onesComplement (bool* array, int arrayLength)
{
    for (int elementNumber = 0; elementNumber < arrayLength; elementNumber++)
    {
        array[elementNumber] = !array[elementNumber];
    }
}

void twosComplement (bool* array, int arrayLength)
{
    
}

void printBoolArray (bool* boolArray, int arrayLength)
{
    for (int elementNumber = arrayLength - 1; elementNumber >= 0; elementNumber--)
    {
        std::cout << boolArray[elementNumber];
    }
}

int main(void)
{
    const int arrayLength = 8;
    bool array1[arrayLength];
    bool array2[arrayLength];
    bool array3[arrayLength];
    decimalToBinary(11, array1, arrayLength);
    decimalToBinary(11, array2, arrayLength);
    multiBitAdder(array1, array2, array3, arrayLength);
    printBoolArray(array3, arrayLength);
    return 0;
}