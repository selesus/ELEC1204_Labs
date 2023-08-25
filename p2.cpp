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

    /* The LSB is placed in the smallest element, the MSB is placed in the smallest element */
    for (int elementNumber = 0; elementNumber < arrayLength; elementNumber++)
    {
        boolArray[elementNumber] = inputNumber % 2;
        inputNumber = inputNumber / 2;
    }

    if (negativeFlag)
    {
        twosComplement(boolArray, arrayLength);
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
    bool oneInBinary[arrayLength];
    oneInBinary[0] = 1;

    /* Initialise subsequent elements with 0 */
    for (int position = arrayLength - 1; position > 0; position--)
    {
        oneInBinary[position] = 0;
    }
    onesComplement(array, arrayLength);
    multiBitAdder(array, oneInBinary, array, arrayLength);
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
    bool outputArray[arrayLength];

    /* 
     *  Certain Functionalities in the lab not added.
     *  Perform twosComplement() on input number if the operation is subtract.
     *  Adding user interface should be relatively simple.
     */
    
    std::cout << "The first input array is:" << std::endl;
    decimalToBinary(1, array1, arrayLength);
    printBoolArray(array1, arrayLength);
    std::cout << '\n';

    std::cout << "The second input array is:" << std::endl;
    decimalToBinary(-1, array2, arrayLength);
    printBoolArray(array2, arrayLength);
    std::cout << '\n';

    std::cout << "The output array is:" << std::endl;
    multiBitAdder(array1, array2, outputArray, arrayLength);
    printBoolArray(outputArray, arrayLength);
    std::cout << '\n';

    return 0;
}