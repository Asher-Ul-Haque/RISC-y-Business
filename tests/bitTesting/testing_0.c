// test_bit.c
#include <stdio.h>
#include <stdlib.h>
#include "../../include/bit.h"

void testCreateFunctions() {
    // Test makeBit
    Bit* bit = makeBit(1);
    printf("Created bit: %d\n", bit->value);

    // Test createBitArray
    unsigned short size = 8;
    Bit* bitArray = createBitArray(size);
    printf("Created bit array: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", bitArray[i].value);
    }
    printf("\n");

    // Don't forget to free dynamically allocated memory
    free(bit);
    free(bitArray);
}

int main() {
    testCreateFunctions();

    // Add more test function calls...

    return 0;
}
