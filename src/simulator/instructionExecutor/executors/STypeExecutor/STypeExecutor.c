#include "STypeExecutor.h"
#include <stdio.h>
#include <stdlib.h>
// - - - - - - - - - - - - - -

sTypeExecutor* initialiseSTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE)
{
    sTypeExecutor* executor = (sTypeExecutor*)malloc(sizeof(sTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    return executor;
}

// - - - - - - - - - - - - -

void destroySTypeExecutor(sTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -

void executeSTypeInstruction(sTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE])
{
    unsigned char rs1 = toDecimal(Instruction, RS1_START, RS1_END, false);
    unsigned char rs2 = toDecimal(Instruction, RS2_START, RS2_END, false);
    short firstHalfImmediate = toDecimal(Instruction, FIRST_HALF_IMMEDIATE_START, FIRST_HALF_IMMEDIATE_END, true);
    short secondHalfImmediate = toDecimal(Instruction, SECOND_HALF_IMMEDIATE_START, SECOND_HALF_IMMEDIATE_END, true);
    short immediate = (secondHalfImmediate << FIRST_HALF_IMMEDIATE_SIZE) | firstHalfImmediate; 
    //We know that the only memory we can access to is the data memory and the stack memory, so first we find if we are in the range
    int address = toDecimal(Instruction, RS1_START, RS2_END, false) + immediate / SCALE_FACTOR;
    if (address >= VIRTUAL_STACK_ADDRESS_START && address <= VIRTUAL_STACK_ADDRESS_END)
    {
        address -= STACK_OFFSET;
        setRegisterValue(&EXECUTOR->registerFile->registers[rs2], EXECUTOR->memoryManager->stackMemory[address].bits);
        return;
    }
    if (address >= VIRTUAL_DATA_ADDRESS_START && address <= VIRTUAL_DATA_ADDRESS_END)
    {
        address -= DATA_OFFSET;
        setRegisterValue(&EXECUTOR->registerFile->registers[rs2], EXECUTOR->memoryManager->dataMemory[address].bits);
        return;
    }
    perror("Invalid memory access\n");
    exit(EXIT_FAILURE);
}
