//Write a test for memory.c that checks that the memory is correctly allocated and deallocated.

#include <stdio.h>
#include "../../src/simulator/memory/memory.h"

int main()
{
    Register stackPointer;
    Memory* memory = allocateMemory(&stackPointer);

    if (memory == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Testing memory allocation: Pass\n");

    // printProgramMemory(memory);
    // printStackMemory(memory);
    // printDataMemory(memory);
    // MemoryCell* memorycell = getMemoryCell(memory, memory->stackMemory[0].address);
    // printMemoryCell(memorycell);
    // Add more test cases or operations as needed
    memory->programMemory[0].bits[0].value = 1;
    Bit address[ADDRESS_SIZE];
    //Give the address of the first program memory cell
    for (int i = 0; i < ADDRESS_SIZE; i++)
    {
        address[i].value = 0;
        printf("%d", address[i].value);
    }
    printf("\n");

    MemoryCell* memorycell = getMemoryCell(memory, address);
    printMemoryCell(memorycell);

    deallocateMemory(memory);

    return 0;
}
