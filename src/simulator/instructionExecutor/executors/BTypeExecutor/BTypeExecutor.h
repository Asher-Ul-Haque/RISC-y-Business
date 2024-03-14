#ifndef B_TYPE_EXECUTOR
#define B_TYPE_EXECUTOR
#include "../../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32

// - - - - - - - - -

typedef struct  
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    unsigned short* programCounter;
} bTypeExecutor;

// - - - - - - - - -

bTypeExecutor* initialiseBTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* programCounter);

void destroyBTypeExecutor(bTypeExecutor* B_TYPE_EXECUTOR);

void executeBTypeInstruction(bTypeExecutor* B_TYPE_EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

// - - - - - - - -

#endif // B_TYPE_EXECUTOR
