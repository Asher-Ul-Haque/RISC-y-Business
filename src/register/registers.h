#ifndef REGISTERS_H
#define REGISTERS_H
#include "../../include/bit.h"
// - - - - - - - - - -

//JUST SOMEBODY: We will have 32 registers of 32 bits each
#define REGISTER_COUNT 32
#define REGISTER_SIZE 32

/*
JUST SOMEBODY: A register is just a 32 bit storage with an ABI name
*/

typedef struct
{
    Bit bits[32];
    char* abi;
} Register;

/*
JUST SOMEBODY: A register file is just an array of registers. 
Register x3 is at index 3
*/

typedef struct
{
    Register registers[REGISTER_COUNT];
} RegisterFile;

/*
JUST SOMEBODY: Here is how init and deallocate will work: take a register file, and then initialise all bits in all registers to 0. We will use only 1 malloc to create all registers
free all registers.
Getting a register by its ABI is as simple as a map.
*/
RegisterFile* init();

void deallocateRegisters(RegisterFile *REGISTER_FILE);

Register* getRegister(RegisterFile *REGISTER_FILE, const char* ABI);

unsigned int hash(const char* abiName);

// - - - - - - - - - -
#endif // REGISTERS_H
