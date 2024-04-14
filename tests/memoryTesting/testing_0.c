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
    printMemoryCell(&memory->stackMemory[0]);
    deallocateMemory(memory);

    return 0;
}
