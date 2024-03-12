#include "bit.h"
#include <stdio.h>
#include <stdlib.h>
// - - - - - - - - - -

Bit* makeBit(bool VALUE)
{
    //JUST_SOMEBODY: I discourage using this function, since malloc = slow
    Bit* newBit = (Bit*)malloc(sizeof(Bit));
    if (newBit == NULL)
    {
        perror("Error allocating memory for Bit");
        exit(EXIT_FAILURE);
    }
    newBit->value = VALUE;
    return newBit;
}

// - - - - - - - - - -

Bit* createBitArray(unsigned short SIZE)
{
    //JUST_SOMEBODY: I discourage using this function since malloc == slow
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Attempted to create an array of invalid size. Acceptable sizes arange from 1 to 32 bits.");
        exit(EXIT_FAILURE);
    }
    
    //Allocate memory for the array
    Bit* newArray = (Bit*)malloc(SIZE * sizeof(Bit));
    if (newArray == NULL)
    {
        perror("Error allocating memory for Bit array");
        exit(EXIT_FAILURE);
    }

    //Intialise every bit to 0
    for (int i = 0; i < SIZE; ++i)
    {
        newArray[i].value = 0;
    }

    //return the array
    return newArray;
}

// - - - - - - - - - 

//JUST SOMEBODY : THE BOOLEAN OPERATIONS

Bit AND(const Bit* BIT_1, const Bit* BIT_2)
{
    Bit result;
    result.value = BIT_1->value & BIT_2->value;
    return result;
}

// - - - - - - - - -

Bit OR(const Bit* BIT_1, const Bit *BIT_2)
{
    Bit result;
    result.value = BIT_1->value | BIT_2->value;
    return result;
}

// - - - - - - - - -

Bit XOR(const Bit* BIT_1, const Bit* BIT_2)
{
    Bit result;
    result.value = BIT_1->value ^ BIT_2->value;
    return result;
}

// - - - - - - - - -

Bit NAND(const Bit *BIT_1, const Bit *BIT_2)
{
    Bit result;
    result.value = !(BIT_1->value & BIT_2->value);
    return result;
}

// - - - - - - - - -

Bit NOR(const Bit *BIT_1, const Bit *BIT_2)
{
    Bit result;
    result.value = !(BIT_1->value | BIT_2->value);
    return result;
}

// - - - - - - - - - 

Bit NOT(const Bit *BIT)
{
    Bit result;
    result.value = !BIT->value;
    return result;
}

// - - - - - - - - -

Bit* bitwiseOR(const Bit* BIT_ARRAY_1, const Bit* BIT_ARRAY_2, unsigned short SIZE)
{

    if (SIZE > 32 || SIZE < 1)
    {
        perror("Attempted to create an array of invalid size. Acceptable sizes arange from 1 to 32 bits.");
        exit(EXIT_FAILURE);
    }

    Bit* result = createBitArray(SIZE);
    for (unsigned short i = 0; i < SIZE; ++i)
    {
        result[i] = OR(&BIT_ARRAY_1[i], &BIT_ARRAY_2[i]);
    }
    return result;
}

// - - - - - - - - -

Bit* bitwiseXOR(const Bit* BIT_ARRAY_1, const Bit* BIT_ARRAY_2, unsigned short SIZE) 
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Attempted to create an array of invalid size. Acceptable sizes arange from 1 to 32 bits.");
        exit(EXIT_FAILURE);
    }

    Bit* result = createBitArray(SIZE);
    for (unsigned short i = 0; i < SIZE; ++i) 
    {
        result[i] = XOR(&BIT_ARRAY_1[i], &BIT_ARRAY_2[i]);
    }
    return result;
}

// - - - - - - - - -

Bit* bitwiseNOT(const Bit* BIT_ARRAY, unsigned short SIZE) 
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Attempted to create an array of invalid size. Acceptable sizes arange from 1 to 32 bits.");
        exit(EXIT_FAILURE);
    }

    Bit* result = createBitArray(SIZE);
    for (unsigned short i = 0; i < SIZE; ++i) 
    {
        result[i] = NOT(&BIT_ARRAY[i]);
    }
    return result;
}

// - - - - - - - - -

//JUST_SOMEBODY: THE ARITHMETIC OPERATIONS, NOT RECOMMENDED TO USE

Bit* ADD(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned short INPUT_ARRAY_SIZE, unsigned short OUTPUT_ARRAY_SIZE)
{
    if (INPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Attempted to create an array of invalid size. Acceptable sizes arange from 1 to 32 bits.");
        exit(EXIT_FAILURE);
    }
    if (OUTPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Attempted to create an array of invalid size. Acceptable sizes range from 1 to 32 bits.");
    }

    Bit* result = createBitArray(OUTPUT_ARRAY_SIZE);
    Bit carry;
    carry.value = 0;

    for (unsigned short i = 0; i < INPUT_ARRAY_SIZE; ++i)
    {
        Bit temp = XOR(&BIT_ARRAY_1[i], &BIT_ARRAY_2[i]);
        result[i] = XOR(&temp, &carry);
        Bit temp1 = AND(&temp, &carry);
        Bit temp2 = AND(&BIT_ARRAY_1[i], &BIT_ARRAY_2[i]);
        carry = OR(&temp1, &temp2);
    }

    result[OUTPUT_ARRAY_SIZE - 1] = carry;

    return result;
}

// - - - - - - - - -


Bit* SUB(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned short INPUT_ARRAY_SIZE, unsigned short OUTPUT_ARRAY_SIZE) {
    if (INPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Attempted to create an array of invalid size. Acceptable sizes arange from 1 to 32 bits.");
        exit(EXIT_FAILURE);
    }
    if (OUTPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Attempted to create an array of invalid size. Acceptable sizes range from 1 to 32 bits.");
    }


    Bit* result = createBitArray(OUTPUT_ARRAY_SIZE);
    Bit borrow;
    borrow.value = 0;

    for (unsigned short i = 0; i < INPUT_ARRAY_SIZE; ++i) {
        Bit temp = XOR(&BIT_ARRAY_1[i], &BIT_ARRAY_2[i]);
        result[i] = XOR(&temp, &borrow);
        Bit temp1 = NOT(&temp);
        Bit temp2 = AND(&temp1, &borrow);
        temp1 = NOT(&BIT_ARRAY_1[i]);
        temp1 = AND(&temp1, &BIT_ARRAY_2[i]);
        borrow = OR(&temp2, &temp1);
//        borrow = OR(&temp2, &AND(&NOT(&BIT_ARRAY_1[i]), &BIT_ARRAY_2[i]));
    }

    // Handling underflow (if borrow is still set after processing all bits)
    // Note: This represents a negative result, which is not supported in this simple implementation
    result[OUTPUT_ARRAY_SIZE - 1] = borrow;

    return result;
}

// - - - - - - - - - -


Bit* MUL(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned short INPUT_ARRAY_SIZE, unsigned short OUTPUT_ARRAY_SIZE) {
    if (INPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Attempted to create an array of invalid size. Acceptable sizes arange from 1 to 32 bits.");
        exit(EXIT_FAILURE);
    }
    if (OUTPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Attempted to create an array of invalid size. Acceptable sizes range from 1 to 32 bits.");
    }

    Bit* result = createBitArray(OUTPUT_ARRAY_SIZE);

    for (unsigned short i = 0; i < INPUT_ARRAY_SIZE; ++i) {
        Bit multiplierBit = BIT_ARRAY_2[i];
        Bit* tempResult = createBitArray(OUTPUT_ARRAY_SIZE);

        for (unsigned short j = 0; j < INPUT_ARRAY_SIZE; ++j) {
            Bit temp = AND(&BIT_ARRAY_1[j], &multiplierBit);
            tempResult[j] = temp;
        }

        // Shift left based on the position of the multiplier bit
        for (unsigned short k = OUTPUT_ARRAY_SIZE - 1; k > i; --k) {
            tempResult[k] = tempResult[k - i];
        }

        // Accumulate the results
        result = ADD(result, tempResult, OUTPUT_ARRAY_SIZE, OUTPUT_ARRAY_SIZE);

        free(tempResult);
    }

    return result;
}

// - - - - - - - -

//JUST SOMEBODY: Increment and decrement functions

void incrementBitArray(Bit* BIT_ARRAY, unsigned short SIZE)
{
    //JUST SOMEBODY: YOU MAY OVERFLOW IF NOT CAREFUL
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Attempted to increment an array of invalid size. Bro, why did you even create it. You know its RISCV32I");
        exit(EXIT_FAILURE);
    }
    
    for (int i = SIZE - 1; i >= 0; --i)
    {
        if (BIT_ARRAY[i].value == 0)
        {
            BIT_ARRAY[i].value = 1;
            break;
        }
        else 
        {
            BIT_ARRAY[i].value = 0;        
        }
    }
}

// - - - - - - - -

void decrementBitArray(Bit* BIT_ARRAY, unsigned short SIZE)
{
    //JUST SOMEBODY: YOU MAY OVERFLOW IF NOT CAREFUL
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Attempted to decrement an array of invalid size. Bro, why did you even create it. You know its RISCV32I");
        exit(EXIT_FAILURE);
    }
    
    for (int i = SIZE - 1; i >= 0; --i)
    {
        if (BIT_ARRAY[i].value == 1)
        {
            BIT_ARRAY[i].value = 0;
            break;
        }
        else 
        {
            BIT_ARRAY[i].value = 1;        
        }
    }
}

// - - - - - - - - - - - -
//JUST SOMEBODY: THE DECIMAL OPERATIONS

Bit* toUnsignedBitArray(int decimal, unsigned short SIZE)
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Attempted to convert an array of invalid size to decimal. Can only handle arrays upto 32 bits and atleast 1 bit.");
        exit(EXIT_FAILURE);
    }
    
    Bit* bitArray = createBitArray(SIZE);
    for (int i = SIZE - 1; i >= 0; --i)
    {
        bitArray[i].value = decimal % 2;
        decimal /=2;
    }

    return bitArray;
}

Bit* toSignedBitArray(int decimal, unsigned short SIZE)
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Attempted to convert an array of invalid size to decimal. Can only handle arrays upto 32 bits and atleast 1 bit.");
        exit(EXIT_FAILURE);
    }

    Bit* bitArray = createBitArray(SIZE);

    if (decimal < 0)
    {
        Bit* absBitArray = toUnsignedBitArray(-decimal, SIZE);

        //Take 2's complement
        for (int i = 0; i < SIZE; ++i)
        {
            absBitArray[i].value = !absBitArray[i].value;
        }

        incrementBitArray(absBitArray, SIZE);

        for (int i = 0; i < SIZE; ++i)
        {
            bitArray[i].value = absBitArray[i].value;
        }

        free(absBitArray);
    }
    else 
    {
        for (int i = SIZE - 1; i >= 0; --i)
        {
            bitArray[i].value = decimal % 2;
            decimal /= 2;
        }
    }

    return bitArray;
}

// - - - - - - - -

int toDecimal(const Bit* BIT_ARRAY, unsigned short SIZE, bool IS_SIGNED)
{
    int decimal = 0;

    for (int i = 0; i < SIZE; ++i)
    {
        decimal = (decimal << 1) | BIT_ARRAY[i].value;
    }

    if (IS_SIGNED && BIT_ARRAY[0].value == 1)
    {
        decimal -= (1 << SIZE);
    }

    return decimal;
}

// - - - - - - - -
