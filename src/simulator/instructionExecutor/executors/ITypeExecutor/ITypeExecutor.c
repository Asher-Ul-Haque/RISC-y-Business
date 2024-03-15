#include "ITypeExecutor.h"
#include <stdlib.h>
// - - - - - - - - - - - - - -

iTypeExecutor* initialiseITypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    iTypeExecutor* executor = (iTypeExecutor*)malloc(sizeof(iTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    executor->programCounter = PROGRAM_COUNTER;
    return executor;
}

// - - - - - - - - - - - - -

void destroyITypeExecutor(iTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -


