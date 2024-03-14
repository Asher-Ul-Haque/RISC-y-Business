#ifndef J_TYPE_EXECUTOR
#define J_TYPE_EXECUTOR
#include "../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32

// - - - - - - - - -

typedef struct  
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    unsigned short* programCounter;
} jTypeExecutor;

// - - - - - - - - -

jTypeExecutor* initialiseJTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* programCounter);

void destroyJTypeExecutor(jTypeExecutor* J_TYPE_EXECUTOR);

void executeJTypeInstruction(jTypeExecutor* J_TYPE_EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

// - - - - - - - -

#endif // J_TYPE_EXECUTOR
