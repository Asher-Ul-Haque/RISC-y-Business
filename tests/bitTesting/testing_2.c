
// test_bit.c
#include <stdio.h>
#include <stdlib.h>
#include "../../include/bit.h"

void testArithmeticFunctions() {
    // Test ADD
    unsigned short size = 8;
    Bit* bitArray1 = createBitArray(size);
    Bit* bitArray2 = createBitArray(size);

    bitArray1[0].value = 1;
    bitArray1[1].value = 1;
    bitArray1[2].value = 1;

    bitArray2[1].value = 1;
    bitArray2[2].value = 1;
    bitArray2[3].value = 1;

    Bit* result = ADD(bitArray1, bitArray2, size, size);
    printf("ADD result: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", result[i].value);
    }
    printf("\n");

    // Test SUB
    Bit* subResult = SUB(bitArray1, bitArray2, size, size);
    printf("SUB result: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", subResult[i].value);
    }
    printf("\n");

    // Test MUL
    Bit* mulResult = MUL(bitArray1, bitArray2, size, size);
    printf("MUL result: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", mulResult[i].value);
    }
    printf("\n");


    // Don't forget to free dynamically allocated memory
    free(bitArray1);
    free(bitArray2);
    free(result);
    free(subResult);
    free(mulResult);
}

int main() {
    // Call other test functions...
    testArithmeticFunctions();

    return 0;
}
