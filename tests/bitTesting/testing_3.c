// test_bit.c
#include <stdio.h>
#include <stdlib.h>
#include "../../include/bit.h"

void testLogicFunctions() {
    // Test AND
    unsigned short size = 8;
    Bit* bitArray1 = createBitArray(size);
    Bit* bitArray2 = createBitArray(size);

    bitArray1[1].value = 1;
    bitArray1[2].value = 1;

    bitArray2[2].value = 1;
    bitArray2[3].value = 1;

    Bit andResult = AND(&bitArray1[1], &bitArray2[2]);
    printf("AND result: %d\n", andResult.value);

    // Test OR
    Bit orResult = OR(&bitArray1[1], &bitArray2[2]);
    printf("OR result: %d\n", orResult.value);

    // Test XOR
    Bit xorResult = XOR(&bitArray1[1], &bitArray2[2]);
    printf("XOR result: %d\n", xorResult.value);

    // Test NAND
    Bit nandResult = NAND(&bitArray1[1], &bitArray2[2]);
    printf("NAND result: %d\n", nandResult.value);

    // Test NOR
    Bit norResult = NOR(&bitArray1[1], &bitArray2[2]);
    printf("NOR result: %d\n", norResult.value);

    // Test NOT
    Bit notResult = NOT(&bitArray1[1]);
    printf("NOT result: %d\n", notResult.value);

    // Don't forget to free dynamically allocated memory
    free(bitArray1);
    free(bitArray2);
}

int main() {
    // Call other test functions...
    testLogicFunctions();

    return 0;
}
