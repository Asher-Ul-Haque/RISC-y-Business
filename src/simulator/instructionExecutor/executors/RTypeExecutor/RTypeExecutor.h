#ifndef R_TYPE_EXECUTOR
#define R_TYPE_EXECUTOR
#include "../../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32

// - - - - - - - - -

typedef struct  
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    unsigned short* programCounter;
} rTypeExecutor;

// - - - - - - - - -

rTypeExecutor* initialiseRTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_cOUNTER);

void destroyRTypeExecutor(rTypeExecutor* EXECUTOR);

void executeRTypeInstruction(rTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

// - - - - - - - -

#endif // R_TYPE_EXECUTOR
