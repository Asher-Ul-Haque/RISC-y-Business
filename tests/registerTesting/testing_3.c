#include <stdio.h>
#include <stdlib.h>
#include "../../src/register/registers.h"

int main()
{
    RegisterFile *registerFile = init();

    printRegisterFile(registerFile);

    const char *testABIs[] = {"zero", "s0", "a3"};

    Register *reg = getRegister(registerFile, "zero");
    Bit newBits[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        newBits[i].value = rand() % 2;
    }
    setRegisterValue(reg, newBits);

    printRegister(reg);

    //Test getAddress function
    printf("Testing getAddress function:\n");
    for (int i = 0; i < sizeof(testABIs) / sizeof(testABIs[0]); ++i)
    {
        const char *abi = testABIs[i];
        const Bit *address = getAddress(registerFile, abi);
        printf("Successfully get address of register %s\n", abi);
        printf("Address: ");
        for (int i = 0; i < 5; ++i)
        {
            printf("%d", address[i].value);
        }
        printf("\n");
    }

    //Test setBit function
    printf("Testing setBit function:\n");
    for (int i = 0; i < sizeof(testABIs) / sizeof(testABIs[0]); ++i)
    {
        const char *abi = testABIs[i];
        Register *reg = getRegister(registerFile, abi);
        Bit newBit;
        newBit.value = rand() % 2;
        setBit(reg, 0, &newBit);
        printf("Successfully set bit 0 of register %s\n", abi);
        printRegister(reg);
    }

    printRegisterFile(registerFile); 

    deallocateRegisters(registerFile);
    return 0;
}
