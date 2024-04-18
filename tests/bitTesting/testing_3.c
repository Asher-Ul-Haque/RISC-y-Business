// test_bit.c
#include <stdio.h>
#include <stdlib.h>
#include "../../include/bit/bit.h"

int main() {
    //Make an array of bits and test the toDecimal function
    Bit bits[32];
    for (int i = 0; i < 30; i++) {
        bits[i].value = 0;
    }
    bits[30].value = 1;
    bits[31].value = 1;   
    int start =30;
    int end = 32;
    for (int i =start; i < end; i++) {
        printf("%d", bits[i].value);
    }
    printf("\n");
    printf("Decimal: %d\n", toDecimal(bits,start, end, true));

    return 0;
}
