#include "registers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// - - - - - - - - - - 

//ABI for all registers
static const char* abi[REGISTER_COUNT] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", 
    "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", 
    "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

/*
JUST SOMEBODY: 
Hashing all the ABI names
We have a simple hash function for mapping to be implement for the getRegister by name function
*/
unsigned int hash(const char* abiName)
{
    unsigned int hashVal = 0;
    while (*abiName)
    {
        hashVal = (hashVal << 5) + *abiName++;
    }
    return hashVal % REGISTER_COUNT;
}

// - - - - - - - - - - -

RegisterFile* init()
{
    RegisterFile *registerFile = (RegisterFile*)malloc(sizeof(RegisterFile));
    if (registerFile == NULL)
    {
        perror("Error allocating memory for registers\nLine: initialising");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < REGISTER_COUNT; ++i)
    {
        for (int j = 0; j < REGISTER_SIZE; ++j)
        {
            registerFile->registers[i].bits[j].value = 0;
            registerFile->registers[i].abi = strdup(abi[i]);
        }
        return registerFile;
    }

    return registerFile;
}

// - - - - - - - - - - - -

void deallocateRegisters(RegisterFile *REGISTER_FILE)
{
    free(REGISTER_FILE);
}

// - - - - - - - - - - - - 

Register* getRegister(RegisterFile *REGISTER_FILE, const char* ABI)
{
    unsigned int index = hash(ABI);
    Register* current = &REGISTER_FILE->registers[index];

    while (current != NULL)
    {
        if (strcmp(current->abi, ABI) == 0)
        {
            return current;
        }
        index = (index + 1) % REGISTER_COUNT;
        current = &REGISTER_FILE->registers[index];
    }
    return NULL;
}

// - - - - - - - - - - -
