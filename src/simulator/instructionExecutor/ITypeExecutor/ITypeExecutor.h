#ifndef I_TYPE_EXECUTOR
#define I_TYPE_EXECUTOR
#include "../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32

// - - - - - - - - -

typedef struct  
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    unsigned short* programCounter;
} iTypeExecutor;

// - - - - - - - - -

iTypeExecutor* initialiseITypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* programCounter);

void destroyITypeExecutor(iTypeExecutor* I_TYPE_EXECUTOR);

void executeITypeLWInstruction(iTypeExecutor* I_TYPE_EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

void executeITypeDefaultInstruction(iTypeExecutor* I_TYPE_EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

void executeITypeJumpInstruction(iTypeExecutor* I_TYPE_EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);
// - - - - - - - -

#endif // I_TYPE_EXECUTOR
