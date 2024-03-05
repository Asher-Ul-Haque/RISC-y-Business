#include "../../src/register/registers.h"

#include <stdio.h>

int main() {
    // Initialize registers
    RegisterFile *registerFile = init();

    // Print the initial values of a few registers
    for (int i = 0; i < 32; ++i) {
        printf("Register %d: ", i);
        for (int j = 31; j >= 0; --j) {
            printf("%d", registerFile->registers[i].bits[j].value);
        }
        printf("\n");
    }

    // Deallocate memory for registers
    deallocateRegisters(registerFile);

    return 0;
}

