#include "../../src/register/registers.h"
#include <stdio.h>


int main()
{
    // Initialize registers
    RegisterFile *registerFile = init();

    printRegisterFile(registerFile);

    // Test getRegister function
    const char *testABIs[] = {"zero", "s0", "a3"};

    printf("Initialise success\n");

    printf("Testing getRegister function:\n");
    for (int i = 0; i < sizeof(testABIs) / sizeof(testABIs[0]); ++i)
    {
        const char *abi = testABIs[i];
        Register *reg = getRegister(registerFile, abi);
        printf("Successfully get register %s\n", reg->abi);

        if (reg != NULL)
        {
            printRegister(reg);
        }
        else
        {
            printf("Register %s not found.\n", abi);
        }
    }

    // Deallocate memory
    deallocateRegisters(registerFile);

    return 0;
}
