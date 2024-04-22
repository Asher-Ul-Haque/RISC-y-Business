#include "simulator.h"
#include "instructionExecutor/executorManager/executorManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// - - - - - - - - -

//Initialise and deinitialise functions

Simulator* initializeSimulator(const char* SIMULATOR_REPORT_PATH)
{
    //Allocate memory for the Simulator struct
    Simulator* simulator = (Simulator*) malloc(sizeof(Simulator));
    simulator->logger = makeLogger(SIMULATOR_REPORT_PATH);
    logMessage(simulator->logger, "Simulator created!");

    if (simulator == NULL)
    {
        perror("Error: Failed to allocate memory for Simulator\n");
    }
    
    //Initialize the register file
    simulator->registerFile = initializeRegisters(simulator->logger
        );
    if (simulator->registerFile == NULL)
    {
        perror("Error: Failed to initialize Register File\n");
        free(simulator);
    }
    logMessage(simulator->logger, "Register file created!");

    //Initialize the memory manager
    simulator->memoryManager = allocateMemory(getRegister(simulator->registerFile, "sp"), simulator->logger);
    if (simulator->memoryManager == NULL)
    {
        perror("Error: Failed to initialize memory manager");
        free(simulator->registerFile);
        free(simulator);
    }
    logMessage(simulator->logger, "Memory allocated!");

    //Initialize the program counter
    unsigned short programCounter = 0; //define the program counter in the stack instead of the heap
    simulator->programCounter = &programCounter;
    if (simulator->programCounter == NULL)
    {
        perror("Error: Failed to initialize program counter");
        free(simulator->memoryManager);
        free(simulator->registerFile);
        free(simulator);
        return NULL;
    }
    *simulator->programCounter = 0;
    logMessage(simulator->logger, "Program counter created");

    simulator->executionManager = initializeExecutorManager(simulator->memoryManager, simulator->registerFile, simulator->programCounter, simulator->logger);
    if (simulator->executionManager == NULL)
    {
        perror("Error: Failed to initialize executor manager");
        free(simulator->memoryManager);
        free(simulator->registerFile);
        free(simulator);
    }

    logMessage(simulator->logger, "Simulator Ready\n- - - - - - - - - - - - - - - \n");
    return simulator;
}

// - - - - - - - - -

void loadProgram(Simulator* SIMULATOR, const char* BINARY_FILE_PATH)
{
    SIMULATOR->binaryFilePath = BINARY_FILE_PATH;
    char message[100];
    sprintf(message, "Loading program from %s into memory", BINARY_FILE_PATH);
    logMessage(SIMULATOR->logger, message);
    loadBinaryToProgramMemory(SIMULATOR->memoryManager, SIMULATOR->binaryFilePath);
    logMessage(SIMULATOR->logger, "successfully loaded program into memory!");
}

// - - - - - - - - -

void deinitializeSimulator(Simulator *SIMULATOR)
{
    free(SIMULATOR->executionManager);
    free(SIMULATOR->memoryManager);
    free(SIMULATOR->registerFile);
    logMessage(SIMULATOR->logger, "Program successfully terminated");
    free(SIMULATOR->logger);
    free(SIMULATOR);
}

// - - - - - - - - - - -

//Print functions:

// void printRegisters(const Simulator *SIMULATOR)
// {
//     //logMessage(SIMULATOR, "Register file for the Simulation");
//     printRegisterFile(SIMULATOR->registerFile);
// }

// - - - - - - - - - - -

// void printMemory(const Simulator *SIMULATOR)
// {
//     //logMessage(SIMULATOR, "Memory manager for the Simulation");
//     printProgramMemory(SIMULATOR->memoryManager);
//     printStackMemory(SIMULATOR->memoryManager);
//     printDataMemory(SIMULATOR->memoryManager);
// }

// - - - - - - - - - - -

bool runNextInstruction(Simulator* SIMULATOR)
{
    if (*SIMULATOR->programCounter >= PROGRAM_MEMORY)
    {
        return false;
    }
    Bit* instruction = getMemoryCell(SIMULATOR->memoryManager, SIMULATOR->memoryManager->programMemory[*SIMULATOR->programCounter/PROGRAM_COUNTER_SCALE_FACTOR].bits)->bits;
    findAndExecute(SIMULATOR->executionManager, instruction);
    return true;
}

// - - - - - - - - - - -

void runSimulation(Simulator *SIMULATOR)
{
    logMessage(SIMULATOR->logger, "Running simulation");

    while (runNextInstruction(SIMULATOR)){}
}

// - - - - - - - - - -
