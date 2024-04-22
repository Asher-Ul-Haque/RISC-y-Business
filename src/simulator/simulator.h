#ifndef SIMULATOR_H
#define SIMULATOR_H
#ifdef __cplusplus
extern "C"{
#endif
#include "instructionExecutor/executorManager/executorManager.h"
// - - - - - - - - - -

#define PROGRAM_COUNTER_SCALE_FACTOR 4
/*
JUST SOMEBODY: A simulator is just a memory manager, a register file, a binary file path and a program counter
We will have a function to initialize the simulator, load the program, execute the instruction, update the program counter, print the registers, print the memory and run the simulation
We will also have a function to deinitialize the simulator
*/

typedef struct 
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    const char* binaryFilePath;
    const char* simulatorReportPath;
    unsigned short* programCounter;
    ExecutorManager* executionManager;
    Logger* logger;
} Simulator;

// - - - - - - - - - - - -

// JUST SOMEBODY: Function prototypes. I want others to review this and add more if needed

Simulator* initializeSimulator(const char* SIMULATOR_REPORT_PATH);

void loadProgram(Simulator* SIMULATOR, const char* BINARY_FILE_PATH);

void printRegisters(const Simulator* SIMULATOR);

void printMemory(const Simulator* SIMULATOR);

void runSimulation(Simulator* SIMULATOR);

bool runNextInstruction(Simulator* SIMULATOR);

void deinitializeSimulator(Simulator* SIMULATOR);

// - - - - - - - - - - - -

#ifdef __cplusplus
}
#endif //extern "C"
#endif /* SIMULATOR_H */
