#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
// - - - - - - - - -

Memory* allocateMemory(Register* STACK_POINTER)
{
    //Allocate memory for the memory
    Memory* memory = (Memory*)malloc(sizeof(Memory));
    if (memory == NULL)
    {
        perror("Error allocating memory for memory\nOperation: initialising");
        exit(EXIT_FAILURE);
    }

    //Set the stackPointer and initialise to 0
    memory->stackPointer = STACK_POINTER;
    Bit zeroBits[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        zeroBits[i].value = 0;
    }
    setRegisterValue(memory->stackPointer, zeroBits);

    //Initialise all bits of all memory cells to 0 and give them their address
    for (int i = 0; i < PROGRAM_MEMORY; ++i)
    {
        for (int j = 0; j < MEMORY_CELL_SIZE; ++j)
        {
            memory->programMemory[i].bits[j].value = 0;
        }
        
        for (int k = ADDRESS_SIZE - 1; k >= 0; --k) 
        {
            memory->programMemory[i].address[k].value = ((i + PROGRAM_ADDRESS_START) >> (ADDRESS_SIZE - k - 1)) & 1;
        }
    }

    for (int i = 0; i < STACK_MEMORY; ++i)
    {
        for (int j = 0; j < MEMORY_CELL_SIZE; ++j)
        {
            memory->stackMemory[i].bits[j].value = 0;
        }
        for (int k = 0; k < ADDRESS_SIZE; ++k)
        {
            memory->stackMemory[i].address[k].value = ((i + STACK_ADDRESS_START) >> (ADDRESS_SIZE - k - 1)) & 1;
        }
    }

    for (int i = 0; i < DATA_MEMORY; ++i)
    {
        for (int j = 0; j < MEMORY_CELL_SIZE; ++j)
        {
            memory->dataMemory[i].bits[j].value = 0;
        }
        for (int k = 0; k < ADDRESS_SIZE; ++k)
        {
            memory->dataMemory[i].address[k].value = ((i + DATA_ADDRESS_START) >> (ADDRESS_SIZE - k - 1)) & 1;
        }
    }

    return memory;
}

// - - - - - - - - -

void deallocateMemory(Memory* MEMORY)
{
    free(MEMORY);
}

// - - - - - - - - -

MemoryCell* getProgramMemory(Memory* MEMORY)
{
    return MEMORY->programMemory;
}

// - - - - - - - - - 

MemoryCell* getStackMemory(Memory* MEMORY)
{
    return MEMORY->stackMemory;
}

// - - - - - - - - -

MemoryCell* getDataMemory(Memory* MEMORY)
{
    return MEMORY->dataMemory;
}

// - - - - - - - - -

void printMemoryCell(const MemoryCell* MEMORYCELL)
{
    printf("Address: ");
    for (int i = 0; i < ADDRESS_SIZE; ++i)
    {
        printf("%d", MEMORYCELL->address[i].value);
    }
    printf(" , Value: ");
    for (int i = 0; i < MEMORY_CELL_SIZE; ++i)
    {
        printf("%d", MEMORYCELL->bits[i].value);
    }
}

// - - - - - - -

void printProgramMemory(const Memory* MEMORY)
{
    printf("\nProgram Memory:\n");
    for (int i = 0; i < PROGRAM_MEMORY; ++i)
    {
        printMemoryCell(&MEMORY->programMemory[i]);
        printf("\n");
    }
}

// - - - - - - - - 

void printStackMemory(const Memory* MEMORY)
{
    printf("\nStack Memory:\n");
    for (int i = 0; i < STACK_MEMORY; ++i)
    {
        printMemoryCell(&MEMORY->stackMemory[i]);
        printf("\n");
    }
}

// - - - - - - - - 

void printDataMemory(const Memory* MEMORY)
{
    printf("\nData Memory:\n");
    for (int i = 0; i < DATA_MEMORY; ++i)
    {
        printMemoryCell(&MEMORY->dataMemory[i]);
        printf("\n");
    }
}

// - - - - - - - -

void decreaseStackPointer(Memory* MEMORY)
{

}
