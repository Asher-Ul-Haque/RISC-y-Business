#ifndef S_TYPE_EXECUTOR
#define S_TYPE_EXECUTOR
#include "../../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32

// - - - - - - - - -

typedef struct  
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    unsigned short* programCounter;
} sTypeExecutor;

// - - - - - - - - -

sTypeExecutor* initialiseSTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* programCounter);

void destroySTypeExecutor(sTypeExecutor* S_TYPE_EXECUTOR);

void executeSTypeInstruction(sTypeExecutor* S_TYPE_EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

// - - - - - - - -

#endif // S_TYPE_EXECUTOR
