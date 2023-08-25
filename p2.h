bool logicalAnd(bool in1, bool in2);
bool logicalOr(bool in1, bool in2);
bool logicalXor(bool in1, bool in2);

struct adderOutput
{
    bool sum;
    bool carryOutput;
};

adderOutput singleAdder(bool in1, bool in2, bool cin);
void decimalToBinary(int inputNumber, bool* boolArray, int arrayLength);
void printBooleanArray(bool* boolArray, int arrayLength);
void multiBitAdder(bool* array1, bool* array2, bool* outputArray, int arrayLength);
void onesComplement(bool* array, int arrayLength);
void twosComplement (bool* array, int arrayLength);