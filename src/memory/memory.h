#ifndef MEMORY_H
#define MEMORY_H
#include "../../include/bit.h"
// - - - - - - - - - 

//JUST SOMEBODY: I am going to create one memory allocate for whole 512 bits, 256 for program, 128 each for stack and data
#define PROGRAM_MEMORY 64 //64 cells of 32 bits each. 256 bytes
#define STACK_MEMORY 32 //32 cells of 32 bits each. 128 bytes
#define DATA_MEMORY 32 //32 cells of 32 bits each. 128 bytes
#define MEMORY_SIZE STACK_MEMORY+PROGRAM_MEMORY+DATA_MEMORY //128 cells of 32 bits each. 512 bytes
#define MEMORY_CELL 32 //32 bits
#define ADDRESS_SIZE 32 //32 bits
#define PROGRAM_ADDRESS_START 0 // 0x00000000
#define PROGRAM_ADDRESS_END 255 // 0x000000FF
#define STACK_ADDRESS_START 256 // 0x00000100 
#define STACK_ADDRESS_END 383 // 0x0000017F
#define DATA_ADDRESS_START 1048576 // 0x00100000
#define DATA_ADDRESS_END 1048703 // 0x0010007F

/* 
JUST SOMEBODY: A memory block is just a 512 byte storage with 256 byte for program. 128 bytes for stack and 128 bytes for data . A memory cell is just a storage of 1 byte with an address
*/

typedef struct
{
    Bit address[ADDRESS_SIZE];
    Bit bits[MEMORY_CELL];
} MemoryCell;

typedef struct
{
    MemoryCell programMemory[PROGRAM_MEMORY];
    MemoryCell stackMemory[STACK_MEMORY];
    MemoryCell dataMemory[DATA_MEMORY];
} Memory;

/*
JUST SOMEBODY: Here is how the memory is going to be allocated. We will have only one malloc for the whole memory. 
Then we will have pointers to the program, stack and data memory. 
Deallocation will be done by freeing the whole memory.
*/


Memory* allocateMemory();

void deallocateMemory(Memory* MEMORY);

MemoryCell* getProgramMemory(Memory* MEMORY);

MemoryCell* getStackMemory(Memory* MEMORY);

MemoryCell* getDataMemory(Memory* MEMORY);

void printMemoryCell(const MemoryCell* MEMORYCELL);

void printStackMemory(const Memory* MEMORY);

void printProgramMemory(const Memory* MEMORY);

void printDataMemory(const Memory* MEMORY);

// - - - - - - - - -

#endif // MEMORY_H

