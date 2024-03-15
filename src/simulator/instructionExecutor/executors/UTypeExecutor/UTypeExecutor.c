#include "UTypeExecutor.h"
#include <stdlib.h>
// - - - - - - - - - - - - - -

uTypeExecutor* initialiseUTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    uTypeExecutor* executor = (uTypeExecutor*)malloc(sizeof(uTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    executor->programCounter = PROGRAM_COUNTER;
    return executor;
}

// - - - - - - - - - - - - -

void destroyUTypeExecutor(uTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -


