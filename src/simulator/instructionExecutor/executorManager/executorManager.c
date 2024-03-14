#include "executorManager.h"
#include <stdio.h>
#include <stdlib.h>

ExecutorManager* initializeExecutorManager(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    //Allocate memory for execution manager
    ExecutorManager* executorManager = (ExecutorManager*)malloc(sizeof(ExecutorManager));
    if (executorManager == NULL)
    {
        perror("Error: failed to create execution manager");
        exit(EXIT_FAILURE);
    }

    //Assign values taken from simulator
    executorManager->registerFile = REGISTER_FILE;
    executorManager->memoryManager = MEMORY_MANAGER;
    executorManager->programCounter = PROGRAM_COUNTER;

    //Assign all types of execution managers
    executorManager->rTypeExecutor = initialiseRTypeExecutor(executorManager->memoryManager, executorManager->registerFile, executorManager->programCounter);
    if (executorManager->rTypeExecutor == NULL)
    {
        perror("Error: failed to attach R Type executor");
        exit(EXIT_FAILURE);
    }

    executorManager->iTypeExecutor = initialiseITypeExecutor(executorManager->memoryManager, executorManager->registerFile, executorManager->programCounter);
    if (executorManager->iTypeExecutor == NULL)
    {
        perror("Error: failed to attach S Type executor");
        exit(EXIT_FAILURE);
    }

    executorManager->sTypeExecutor = initialiseSTypeExecutor(executorManager->memoryManager, executorManager->registerFile, executorManager->programCounter);
    if (executorManager->sTypeExecutor == NULL)
    {
        perror("Error: failed to attach S Type executor");
        exit(EXIT_FAILURE);
    }

    executorManager->bTypeExecutor = initialiseBTypeExecutor(executorManager->memoryManager, executorManager->registerFile, executorManager->programCounter);
    if (executorManager->bTypeExecutor == NULL)
    {
        perror("Error: failed to attach B Type executor");
        exit(EXIT_FAILURE);
    }

    executorManager->uTypeExecutor = initialiseUTypeExecutor(executorManager->memoryManager, executorManager->registerFile, executorManager->programCounter);
    if (executorManager->uTypeExecutor == NULL)
    {
        perror("Error: failed to attach U Type executor");
        exit(EXIT_FAILURE);
    }

    executorManager->jTypeExecutor = initialiseJTypeExecutor(executorManager->memoryManager, executorManager->registerFile, executorManager->programCounter);
    if (executorManager->jTypeExecutor == NULL)
    {
        perror("Error: failed to attach J Type executor");
        exit(EXIT_FAILURE);
    }

    return executorManager;
}

// - - - - - - - - - - - - -

