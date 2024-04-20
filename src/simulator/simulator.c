#include "simulator.h"
#include "instructionExecutor/executorManager/executorManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// - - - - - - - - -

//Initialise and deinitialise functions

Simulator* initializeSimulator()
{
    //Allocate memory for the Simulator struct
    printf("Creating simulator\n");
    Simulator* simulator = (Simulator*) malloc(sizeof(Simulator));

/*
    time_t currentTime;
    struct tm *localTime;
    currentTime = time(NULL);
    localTime = localtime(&currentTime);
    simulator->//logFilePath = "//log.txt";
    //Open the //log file in write mode
    FILE* //logFile = fopen(simulator->//logFilePath, "w");
    if (//logFile == NULL)
    {
        perror("Error: Failed to open //log file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(//logFile, "//log file created at %s\n", asctime(localTime));
    fclose(//logFile);
*/
    if (simulator == NULL)
    {
        perror("Error: Failed to allocate memory for Simulator\n");
        exit(EXIT_FAILURE);
    }
    
    //Initialize the register file
    simulator->registerFile = initializeRegisters();
    if (simulator->registerFile == NULL)
    {
        perror("Error: Failed to initialize Register File\n");
        free(simulator);
        exit(EXIT_FAILURE);
    }

    //Initialize the memory manager
    simulator->memoryManager = allocateMemory(getRegister(simulator->registerFile, "sp"));
    if (simulator->memoryManager == NULL)
    {
        perror("Error: Failed to initialize memory manager");
        free(simulator->registerFile);
        free(simulator);
        return NULL;
    }

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
    //log(simulator, "Program counter created");

    simulator->executionManager = initializeExecutorManager(simulator->memoryManager, simulator->registerFile, simulator->programCounter);
    if (simulator->executionManager == NULL)
    {
        perror("Error: Failed to initialize executor manager");
        free(simulator->memoryManager);
        free(simulator->registerFile);
        free(simulator);
    }

    //log(simulator, "Simulator created\n");
    return simulator;
}

// - - - - - - - - -

void loadProgram(Simulator* SIMULATOR, const char* BINARY_FILE_PATH)
{
    SIMULATOR->binaryFilePath = BINARY_FILE_PATH;
    //log(SIMULATOR, "Loading program into memory\n");
    loadBinaryToProgramMemory(SIMULATOR->memoryManager, SIMULATOR->binaryFilePath);
}

// - - - - - - - - -

void deinitializeSimulator(Simulator *SIMULATOR)
{
    free(SIMULATOR->executionManager);
    free(SIMULATOR->memoryManager);
    free(SIMULATOR->registerFile);
    free(SIMULATOR);

    //log(SIMULATOR, "Program successfully terminated");
    exit(EXIT_SUCCESS);
}

// - - - - - - - - - - -

//Print functions:

void printRegisters(const Simulator *SIMULATOR)
{
    //log(SIMULATOR, "Register file for the Simulation");
    printRegisterFile(SIMULATOR->registerFile);
}

// - - - - - - - - - - -

void printMemory(const Simulator *SIMULATOR)
{
    //log(SIMULATOR, "Memory manager for the Simulation");
    printProgramMemory(SIMULATOR->memoryManager);
    printStackMemory(SIMULATOR->memoryManager);
    printDataMemory(SIMULATOR->memoryManager);
}

// - - - - - - - - - - -

void //log(Simulator *SIMULATOR, const char* MESSAGE)
{
    FILE* //logFile = fopen(SIMULATOR->//logFilePath, "a");
    if (//logFile == NULL)
    {
        FILE* //logFile = fopen(SIMULATOR->//logFilePath, "w");
    }

    fprintf(//logFile, "%s\n", MESSAGE);
    fprintf(//logFile, "\n");
    fprintf(//logFile, "\n");
    fprintf(//logFile, "\n");
    fprintf(//logFile, "\n");

    fclose(//logFile);
}

// - - - - - - - - - - -

void runSimulation(Simulator *SIMULATOR)
{
    //log(SIMULATOR, "Running simulation");

    while (!(*SIMULATOR->programCounter >= PROGRAM_MEMORY))
    {
    //     Bit* instruction = getMemoryCell(SIMULATOR->memoryManager, SIMULATOR->memoryManager->programMemory[*SIMULATOR->programCounter/PROGRAM_COUNTER_SCALE_FACTOR].bits)->bits;
    //     findAndExecute(SIMULATOR->executionManager, instruction);
    //     printRegisters(SIMULATOR);
    // }
        //make an array of bits with this value 00000000000000000000010010110011
        // Bit* instruction = getMemoryCell(SIMULATOR->memoryManager, SIMULATOR->memoryManager->programMemory[*SIMULATOR->programCounter/PROGRAM_COUNTER_SCALE_FACTOR].bits)->bits;
        Bit* instruction = getMemoryCell(SIMULATOR->memoryManager, SIMULATOR->memoryManager->programMemory[*SIMULATOR->programCounter/PROGRAM_COUNTER_SCALE_FACTOR].bits)->bits;
        findAndExecute(SIMULATOR->executionManager, instruction);
        ////log the program counter and the integer value it stores
        printf("Program counter: %d\n", *SIMULATOR->programCounter);

        instruction = getMemoryCell(SIMULATOR->memoryManager, SIMULATOR->memoryManager->programMemory[*SIMULATOR->programCounter/PROGRAM_COUNTER_SCALE_FACTOR].bits)->bits;
        findAndExecute(SIMULATOR->executionManager, instruction);
        printf("Program counter: %d\n", *SIMULATOR->programCounter);

}

// - - - - - - - - - -
