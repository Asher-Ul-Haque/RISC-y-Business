#include "simulator.h"
#include "memory/memory.h"
#include "register/registers.h"
#include <stdio.h>
#include <stdlib.h>
// - - - - - - - - -

//Initialise and deinitialise functions

Simulator* initializeSimulator(const char* BINARY_FILE_PATH)
{
    printf("Creating simulator\n");
    Simulator* simulator = (Simulator*) malloc(sizeof(Simulator));
    simulator->registerFile = initializeRegisters();
    simulator->memoryManager = allocateMemory(getRegister(simulator->registerFile, "sp"));
    simulator->programCounter = 0;
    simulator->binaryFilePath = BINARY_FILE_PATH;
    printf("Simulator created\n");
    printRegisterFile(simulator->registerFile);
    printf("\n\n");
    printProgramMemory(simulator->memoryManager);
    printStackMemory(simulator->memoryManager);
    printDataMemory(simulator->memoryManager);
    printf("%s\n\n", simulator->binaryFilePath);
    loadProgram(simulator);
    printf("%s", "Ready to execute"); 
    return simulator;
}

// - - - - - - - - -

void loadProgram(Simulator *SIMULATOR)
{
    loadBinaryToProgramMemory(SIMULATOR->memoryManager, SIMULATOR->binaryFilePath);
}

// - - - - - - - - -

void deinitializeSimulator(Simulator *SIMULATOR)
{
    free(SIMULATOR);
    printf("Program successfully terminated");
    exit(EXIT_SUCCESS);
}

// - - - - - - - - - - -

//Print functions:

void printRegisters(const Simulator *SIMULATOR)
{
    printf("Register file for the Simulation %s: ", *SIMULATOR);
    printRegisterFile(SIMULATOR->registerFile);
}

// - - - - - - - - - - -

void printMemory(const Simulator *SIMULATOR)
{
    printf("Memory manager for the Simulation %s: ", *SIMULATOR);
    printProgramMemory(SIMULATOR->memoryManager);
    printStackMemory(SIMULATOR->memoryManager);
    printDataMemory(SIMULATOR->memoryManager);
}

// - - - - - - - - - - -


