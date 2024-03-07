#include "../../src/register/registers.h"

#include <stdio.h>

int main() {
    // Initialize registers
    RegisterFile *registerFile = init();
    
    static const char* abi[REGISTER_COUNT] = {
        "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", 
        "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", 
        "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
    };

    // Print the initial values of a few registers
    for (int i = 0; i < REGISTER_COUNT; ++i)
    {
        const char* currentABI = abi[i];
        printf("%s: ", currentABI);

        for (int j = 31; j >=0; --j)
        {
            printf("%d", registerFile->registers[i].bits[j].value);
        }
        printf("\n");
    }


    // Deallocate memory for registers
    deallocateRegisters(registerFile);

    return 0;
}

