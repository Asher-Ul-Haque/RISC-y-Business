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
    //JUST_SOMEBODY: Throw error on underflow;
    if (toDecimal(MEMORY->stackPointer->bits, REGISTER_SIZE, false) < STACK_ADDRESS_START)
    {
        perror("Stack Underflow");
        exit(EXIT_FAILURE);
    }

    decrementBitArray(MEMORY->stackPointer->bits, REGISTER_SIZE);
}

// - - - - - - - -

void increaseStackPointer(Memory* MEMORY)
{
    //JUST_SOMEBODY: Throw error on underflow;
    if (toDecimal(MEMORY->stackPointer->bits, REGISTER_SIZE, false) > STACK_ADDRESS_END)
    {
        perror("Stack Overflow! Very punny!");
        exit(EXIT_FAILURE);
    }

    incrementBitArray(MEMORY->stackPointer->bits, REGISTER_SIZE);
}

// - - - - - - - - -

static bool isAddressInRange(const Bit ADDRESS[ADDRESS_SIZE], int start, int end)
{
    for (int i = 0; i < ADDRESS_SIZE; ++i)
    {
        if (ADDRESS[i].value != ((start >> (ADDRESS_SIZE - 1 -i)) & 1))
        {
            return 0; //ADDRESS DOESNT MATCH
        }
    }

    return 1; //ADDRESS IS IN THE VALID RANGE
}

// - - - - - - - - - -

int calculateMemoryIndex(const Bit ADDRESS[ADDRESS_SIZE])
{
    int index = 0;

    for (int i = 0; i < ADDRESS_SIZE; ++i)
    {
        index = (index << 1) | ADDRESS[i].value;
    }

    return index;
}

// - - - - - - - - - -

MemoryCell* getMemoryCell(Memory* MEMORY, const Bit ADDRESS[ADDRESS_SIZE])
{
    if (isAddressInRange(ADDRESS, PROGRAM_ADDRESS_START, PROGRAM_ADDRESS_END))
    {
        return &MEMORY->programMemory[calculateMemoryIndex(ADDRESS)];
    }
    if (isAddressInRange(ADDRESS, STACK_ADDRESS_START, STACK_ADDRESS_END))
    {
        return &MEMORY->stackMemory[calculateMemoryIndex(ADDRESS)];
    } 
    if (isAddressInRange(ADDRESS, DATA_ADDRESS_START, DATA_ADDRESS_END))
    {
        return &MEMORY->dataMemory[calculateMemoryIndex(ADDRESS)];
    }

    return NULL;
}

// - - - - - - - - - -

void pushStackMemory(Memory* MEMORY, const Register* REGISTER)
{
    if (toDecimal(MEMORY->stackPointer->bits, REGISTER_SIZE, false) > STACK_ADDRESS_END)
    {
        perror("Stack Overflow! Very punny");
        exit(EXIT_FAILURE);
    }

    MemoryCell* stackTopCell = getMemoryCell(MEMORY, MEMORY->stackPointer->bits);

    for (int i = 0; i < MEMORY_CELL_SIZE; ++i)
    {
        stackTopCell->bits[i].value = REGISTER->bits[i].value;
    }

    increaseStackPointer(MEMORY);
}

// - - - - - - - - -

Bit* popStackMemory(Memory* MEMORY)
{
    if (toDecimal(MEMORY->stackPointer->bits, REGISTER_SIZE, false) < STACK_ADDRESS_START)
    {
        perror("Stack Underflow");
        exit(EXIT_FAILURE);
    }

    MemoryCell* stackTopCell = getMemoryCell(MEMORY, MEMORY->stackPointer->bits);
    decreaseStackPointer(MEMORY);
    return stackTopCell->bits;
}

// - - - - - - - - -

void setDataMemoryCell(Memory* MEMORY, const Bit ADDRESS[ADDRESS_SIZE], const Bit* VALUE)
{
    if (!isAddressInRange(ADDRESS, DATA_ADDRESS_START, DATA_ADDRESS_END))
    {
        perror("Invalid data address");
        exit(EXIT_FAILURE);
    }

    MemoryCell* dataMemoryCell = getMemoryCell(MEMORY, ADDRESS);

    for (int i = 0; i < MEMORY_CELL_SIZE; ++i)
    {
        dataMemoryCell->bits[i].value = VALUE[i].value;
    }
}

// - - - - - - - - -

void loadBinaryToProgramMemory(Memory* MEMORY, const char* RELATIVE_FILE_PATH)
{
    FILE* file = fopen(RELATIVE_FILE_PATH, "r");

    if (file == NULL)
    {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    char line[MEMORY_CELL_SIZE + 1]; //JUST SOMEBODY: plus one for the \n character.

    //JUST SOMEBODY: Reading each line and storing it in the programMemory for the simulator to execute
    for (int i = 0; i < PROGRAM_MEMORY; ++i)
    {
        if (fgets(line, sizeof(line), file) == NULL) //JUST SOMEBODY: @Kepi, fgets can get a set number of characters if we want
        {
            break; //REACHED END OF FILE
        }
        
        Bit* programMemoryBits[MEMORY_CELL_SIZE];

        for (int j = 0; j < MEMORY_CELL_SIZE; ++j)
        {
            switch(line[j])
            {
                case '0':
                    programMemoryBits[j]->value = 0;
                case '1':
                    programMemoryBits[j]->value = 1;
                default:
                    perror("Encountered a non-binary character while reading the file");
                    exit(EXIT_FAILURE);
            }
        }

        MemoryCell* programMemoryCell = &MEMORY->programMemory[i];
        for (int j = 0; j < MEMORY_CELL_SIZE; ++j)
        {
            programMemoryCell->bits[j].value = programMemoryBits[j]->value;
        }

    }
    fclose(file);
}
