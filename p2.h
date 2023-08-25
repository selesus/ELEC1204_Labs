bool logicalAnd(bool in1, bool in2);
bool logicalOr(bool in1, bool in2);
bool logicalXor(bool in1, bool in2);

struct adderOutput
{
    bool sum;
    bool carryOutput;
};

adderOutput singleAdder(bool in1, bool in2, bool cin);