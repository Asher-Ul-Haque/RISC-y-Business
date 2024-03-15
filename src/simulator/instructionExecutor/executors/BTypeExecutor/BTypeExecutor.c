#include "BTypeExecutor.h"
#include <stdlib.h>
// - - - - - - - - - - - - - -

bTypeExecutor* initialiseBTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    bTypeExecutor* executor = (bTypeExecutor*)malloc(sizeof(bTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    executor->programCounter = PROGRAM_COUNTER;
    return executor;
}

// - - - - - - - - - - - - -

void destroyBTypeExecutor(bTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -


