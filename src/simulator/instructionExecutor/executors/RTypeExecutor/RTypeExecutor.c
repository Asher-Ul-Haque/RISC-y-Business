#include "RTypeExecutor.h"
#include <stdlib.h>
// - - - - - - - - - - - - - -

rTypeExecutor* initialiseRTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    rTypeExecutor* executor = (rTypeExecutor*)malloc(sizeof(rTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    executor->programCounter = PROGRAM_COUNTER;
    return executor;
}

// - - - - - - - - - - - - -

void destroyRTypeExecutor(rTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -


