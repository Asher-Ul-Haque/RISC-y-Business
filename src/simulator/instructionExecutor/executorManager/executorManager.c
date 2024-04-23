#include "executorManager.h"
#include <stdio.h>
#include <stdlib.h>

ExecutorManager* initializeExecutorManager(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER, Logger* LOGGER)
{
    //Allocate memory for execution manager
    ExecutorManager* executorManager = (ExecutorManager*)malloc(sizeof(ExecutorManager));
    if (executorManager == NULL)
    {
        perror("Error: failed to create execution manager");
    }

    //Assign values taken from simulator
    executorManager->registerFile = REGISTER_FILE;
    executorManager->memoryManager = MEMORY_MANAGER;
    executorManager->programCounter = PROGRAM_COUNTER;

    //Assign all types of execution managers
    executorManager->rTypeExecutor = initialiseRTypeExecutor(executorManager->memoryManager, executorManager->registerFile);
    if (executorManager->rTypeExecutor == NULL)
    {
        perror("Error: failed to attach R Type executor");
    }

    executorManager->iTypeExecutor = initialiseITypeExecutor(executorManager->memoryManager, executorManager->registerFile, executorManager->programCounter);
    if (executorManager->iTypeExecutor == NULL)
    {
        perror("Error: failed to attach S Type executor");
    }

    executorManager->sTypeExecutor = initialiseSTypeExecutor(executorManager->memoryManager, executorManager->registerFile);
    if (executorManager->sTypeExecutor == NULL)
    {
        perror("Error: failed to attach S Type executor");
    }

    executorManager->bTypeExecutor = initialiseBTypeExecutor(executorManager->memoryManager, executorManager->registerFile, executorManager->programCounter);
    if (executorManager->bTypeExecutor == NULL)
    {
        perror("Error: failed to attach B Type executor");
    }

    executorManager->uTypeExecutor = initialiseUTypeExecutor(executorManager->memoryManager, executorManager->registerFile, executorManager->programCounter);
    if (executorManager->uTypeExecutor == NULL)
    {
        perror("Error: failed to attach U Type executor");
    }

    executorManager->jTypeExecutor = initialiseJTypeExecutor(executorManager->memoryManager, executorManager->registerFile, executorManager->programCounter);
    if (executorManager->jTypeExecutor == NULL)
    {
        perror("Error: failed to attach J Type executor");
    }

    executorManager->logger = LOGGER;

    executorManager->ioTypeExecutor = initialiseIOTypeExecutor(executorManager->memoryManager, executorManager->registerFile, executorManager->logger);
    if (executorManager->ioTypeExecutor == NULL)
    {
        perror("Error: failed to attach IO Type executor");
    }

    return executorManager;
}

// - - - - - - - - - - - - -

void destroyExecutorManager(ExecutorManager * EXECUTION_MANAGER)
{
    if (EXECUTION_MANAGER == NULL)
    {
        perror("Error: failed to destroy execution manager");
    }

    //Destroy all types of execution managers
    destroyRTypeExecutor(EXECUTION_MANAGER->rTypeExecutor);
    destroyITypeExecutor(EXECUTION_MANAGER->iTypeExecutor);
    destroySTypeExecutor(EXECUTION_MANAGER->sTypeExecutor);
    destroyBTypeExecutor(EXECUTION_MANAGER->bTypeExecutor);
    destroyUTypeExecutor(EXECUTION_MANAGER->uTypeExecutor);
    destroyJTypeExecutor(EXECUTION_MANAGER->jTypeExecutor);
    destroyIOTypeExecutor(EXECUTION_MANAGER->ioTypeExecutor);

    //Free memory
    free(EXECUTION_MANAGER);
}

// - - - - - - - - - - - - -

void findAndExecute(ExecutorManager* EXECUTION_MANAGER, Bit INSTRUCTION[INSTRUCTION_SIZE])
{ 
    //Print the opcode
    //printf("\nMessasge from findAndExecute\n");
    //Revese the instruction array interely
    // for (int i = 0; i < INSTRUCTION_SIZE/2; i++)
    // {
    //     Bit temp = INSTRUCTION[i];
    //     INSTRUCTION[i] = INSTRUCTION[INSTRUCTION_SIZE - i - 1];
    //     INSTRUCTION[INSTRUCTION_SIZE - i - 1] = temp;
    // }
    unsigned char opcode = toDecimal(INSTRUCTION, OPCODE_START, OPCODE_END, false);
    printf("Opcode: %d\n", opcode);
    switch(opcode)
    {
        case R_TYPE:
            //printf("R Type\n");
            executeRTypeInstruction(EXECUTION_MANAGER->rTypeExecutor, INSTRUCTION);
            *EXECUTION_MANAGER->programCounter += 4;
            break;
        
        case I_TYPE_LW:
            //printf("I Type LW\n");
            executeITypeLWInstruction(EXECUTION_MANAGER->iTypeExecutor, INSTRUCTION);
            *EXECUTION_MANAGER->programCounter += 4;
            break;
        case I_TYPE_DEFAULT:
            //printf("I Type Default\n");
            executeITypeDefaultInstruction(EXECUTION_MANAGER->iTypeExecutor, INSTRUCTION);
            *EXECUTION_MANAGER->programCounter += 4;
            break;
        case I_TYPE_JUMP:
            //printf("I Type Jump\n");
            executeITypeJumpInstruction(EXECUTION_MANAGER->iTypeExecutor, INSTRUCTION);
            break;

        case S_TYPE:
            //printf("S Type\n");
            executeSTypeInstruction(EXECUTION_MANAGER->sTypeExecutor, INSTRUCTION);
            *EXECUTION_MANAGER->programCounter+= 4;
            break;
        
        case B_TYPE:
            executeBTypeInstruction(EXECUTION_MANAGER->bTypeExecutor, INSTRUCTION);
            break;

        case U_TYPE_1:
            executeUType1Instruction(EXECUTION_MANAGER->uTypeExecutor, INSTRUCTION);
            break;
        case U_TYPE_2:
            executeUType2Instruction(EXECUTION_MANAGER->uTypeExecutor, INSTRUCTION);
            break;
        
        case J_TYPE:
            executeJTypeInstruction(EXECUTION_MANAGER->jTypeExecutor, INSTRUCTION);
            break;

        case IO_TYPE:
            executeIOTypeInstruction(EXECUTION_MANAGER->ioTypeExecutor, INSTRUCTION);
            *EXECUTION_MANAGER->programCounter+= 4;
            break;
    
        case HALT:
            logMessage(EXECUTION_MANAGER->logger, "\n- - - - - - - - - - - - \nExecution Complete\n");
            
        default:
            perror("Error: unknown opcode");
    }
}

