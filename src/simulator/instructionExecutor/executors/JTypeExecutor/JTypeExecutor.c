#include "JTypeExecutor.h"
#include <stdlib.h>
// - - - - - - - - - - - - - -

jTypeExecutor* initialiseJTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    jTypeExecutor* executor = (jTypeExecutor*)malloc(sizeof(jTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    executor->programCounter = PROGRAM_COUNTER;
    return executor;
}

// - - - - - - - - - - - - -

void destroyJTypeExecutor(jTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -


