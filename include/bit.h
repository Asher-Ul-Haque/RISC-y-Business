#ifndef BIT_H
#define BIT_H
#include <stdbool.h>
// - - - - - - - - - -

#define BIT_ARRAY_SIZE 32;
/*
JUST SOMEBODY: This is how we will define a bit: a struct with just a boolean value of size 1 
Here is how we can use it:
int main()
{
    Bit myBit;
    myBit.value = 0; //Reset the bit
    myBit.value = 1; //Set the bit
}

If you give more than 1 as a value, the bit is considered set.
*/

typedef struct 
{
    bool value : 1;
} Bit;

Bit* makeBit(bool VALUE);

Bit* createBitArray(unsigned short SIZE);

Bit AND(const Bit* BIT_1, const Bit* BIT_2);

Bit OR(const Bit* BIT_1, const Bit* BIT_2);

Bit XOR(const Bit* BIT_1, const Bit* BIT_2);

Bit NAND(const Bit* BIT_1, const Bit* BIT_2);

Bit NOR(const Bit* BIT_1, const Bit* BIT_2);

Bit NOT(const Bit* BIT);

Bit* bitwiseOR(const Bit* BIT_ARRAY_1, const Bit* BIT_ARRAY_2, unsigned short SIZE);

Bit* bitwiseXOR(const Bit* BIT_ARRAY_1, const Bit* BIT_ARRAY_2, unsigned short SIZE);

Bit* bitwiseNOT(const Bit* BIT_ARRAY, unsigned short SIZE);

void incrementBitArray(Bit* BIT_ARRAY, unsigned short SIZE);

void decrementBitArray(Bit* BIT_ARRAY, unsigned short SIZE);

Bit* ADD(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned short INPUT_ARRAY_SIZE, unsigned short OUTPUT_ARRAY_SIZE); 

Bit* SUB(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned short INPUT_ARRAY_SIZE, unsigned short OUTPUT_ARRAY_SIZE); 

Bit* MUL(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned short INPUT_ARRAY_SIZE, unsigned short OUTPUT_ARRAY_SIZE); 

Bit* toUnsignedBitArray(int decimal, unsigned short SIZE);

Bit* toSignedBitArray(int decimal, unsigned short SIZE);

int toDecimal(Bit* BIT_ARRAY, unsigned short SIZE, bool IS_SIGNED);
// - - - - - - - - - - 
#endif //BIT_H
