//Write a test for memory.c that checks that the memory is correctly allocated and deallocated.

#include <stdio.h>
#include "../../src/memory/memory.h"

int main()
{
    Memory* memory = allocateMemory();

    if (memory == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Testing memory allocation: Pass\n");

    printProgramMemory(memory);
    printStackMemory(memory);
    printDataMemory(memory);

    // Add more test cases or operations as needed

    deallocateMemory(memory);

    return 0;
}
