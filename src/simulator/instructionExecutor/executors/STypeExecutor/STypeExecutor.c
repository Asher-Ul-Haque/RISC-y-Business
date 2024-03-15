#include "STypeExecutor.h"
#include <stdlib.h>
// - - - - - - - - - - - - - -

sTypeExecutor* initialiseSTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    sTypeExecutor* executor = (sTypeExecutor*)malloc(sizeof(sTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    executor->programCounter = PROGRAM_COUNTER;
    return executor;
}

// - - - - - - - - - - - - -

void destroySTypeExecutor(sTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -


