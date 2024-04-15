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
    executorManager->rTypeExecutor = initialiseRTypeExecutor(executorManager->memoryManager, executorManager->registerFile);
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

    executorManager->sTypeExecutor = initialiseSTypeExecutor(executorManager->memoryManager, executorManager->registerFile);
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

void destroyExecutorManager(ExecutorManager * EXECUTION_MANAGER)
{
    if (EXECUTION_MANAGER == NULL)
    {
        perror("Error: failed to destroy execution manager");
        exit(EXIT_FAILURE);
    }

    //Destroy all types of execution managers
    destroyRTypeExecutor(EXECUTION_MANAGER->rTypeExecutor);
    destroyITypeExecutor(EXECUTION_MANAGER->iTypeExecutor);
    destroySTypeExecutor(EXECUTION_MANAGER->sTypeExecutor);
    destroyBTypeExecutor(EXECUTION_MANAGER->bTypeExecutor);
    destroyUTypeExecutor(EXECUTION_MANAGER->uTypeExecutor);
    destroyJTypeExecutor(EXECUTION_MANAGER->jTypeExecutor);

    //Free memory
    free(EXECUTION_MANAGER);
}

// - - - - - - - - - - - - -

void findAndExecute(ExecutorManager* EXECUTION_MANAGER, Bit INSTRUCTION[INSTRUCTION_SIZE])
{ 
    for(int i = 0; i < INSTRUCTION_SIZE; i++)
    {
        printf("instruction[%d]: %d\n", i, INSTRUCTION[i]);
    }
    Bit* toConvertToOpcode = (Bit*)malloc(sizeof(Bit) * 7);
    int j = 0;
    for (int i = 6; i >= 0; --i){
        // printf("instruction[%d]: %d\n", i, INSTRUCTION[i]);
        toConvertToOpcode[j] = INSTRUCTION[i];
        j++;
    }
    unsigned char opcode = toDecimal(toConvertToOpcode, OPCODE_START, OPCODE_END, false);
    printf("Opcode: %d\n", opcode);
    switch(opcode)
    {
        case R_TYPE:
            printf("R Type\n");
            printf("Opcode: %d\n", opcode);
            executeRTypeInstruction(EXECUTION_MANAGER->rTypeExecutor, INSTRUCTION);
            EXECUTION_MANAGER->programCounter+= 4;
            break;
        
        case I_TYPE_LW:
            executeITypeLWInstruction(EXECUTION_MANAGER->iTypeExecutor, INSTRUCTION);
            break;
        case I_TYPE_DEFAULT:
            executeITypeDefaultInstruction(EXECUTION_MANAGER->iTypeExecutor, INSTRUCTION);
            break;
        case I_TYPE_JUMP:
            executeITypeJumpInstruction(EXECUTION_MANAGER->iTypeExecutor, INSTRUCTION);
            break;

        case S_TYPE:
            executeSTypeInstruction(EXECUTION_MANAGER->sTypeExecutor, INSTRUCTION);
            EXECUTION_MANAGER->programCounter+= 4;
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
    
        case HALT:
            printf("Execution Complete\n");
            exit(EXIT_SUCCESS);
        default:
            perror("Error: unknown opcode");
            exit(EXIT_FAILURE);
    }
}

