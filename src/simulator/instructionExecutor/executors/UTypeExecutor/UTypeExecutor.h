#ifndef U_TYPE_EXECUTOR
#define U_TYPE_EXECUTOR
#include "../../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32

// - - - - - - - - -

typedef struct  
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    unsigned short* programCounter;
} uTypeExecutor;

// - - - - - - - - -

uTypeExecutor* initialiseUTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* programCounter);

void destroyUTypeExecutor(uTypeExecutor* EXECUTOR);

void executeUType1Instruction(uTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

void executeUType2Instruction(uTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

// - - - - - - - -

#endif // U_TYPE_EXECUTOR
