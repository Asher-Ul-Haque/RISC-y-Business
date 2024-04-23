#include "IOTypeExecutor.h"
#include <stdio.h>
#include <stdlib.h>
// - - - - - - - - - - - -

ioTypeExecutor* initialiseIOTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, Logger* LOGGER)
{
	ioTypeExecutor* executor = (ioTypeExecutor*)malloc(sizeof(ioTypeExecutor));
	executor->memoryManager = MEMORY_MANAGER;
	executor->registerFile = REGISTER_FILE;
	executor->logger = LOGGER;
	return executor;
}

// - - - - - - - - - - - - - - -

void destroyIOTypeExecutor(ioTypeExecutor* EXECUTOR)
{
	free(EXECUTOR);
}

// - - - - - - - - - - - - - - - -

void executeIOTypeInstruction(ioTypeExecutor* EXECUTOR, Bit INSTRUCTION[INSTRUCTION_SIZE])
{
	char funct3 = toDecimal(INSTRUCTION, FUNCT3_START, FUNCT3_END, false);
	int memoryAddress = toDecimal(INSTRUCTION, MEMORY_START, MEMORY_END, false);
	int registerAddress = toDecimal(INSTRUCTION, RD_START, RD_END, false);
	switch (funct3)
	{
		case PRINT_MEMORY_CELL:
			if (memoryAddress >= VIRTUAL_STACK_ADDRESS_START && memoryAddress <= VIRTUAL_STACK_ADDRESS_END)
		    {
		        memoryAddress -= STACK_OFFSET;
		        printMemoryCell(&EXECUTOR->memoryManager->stackMemory[memoryAddress/4], EXECUTOR->logger);
		        return;
		    }

		    if (memoryAddress >= VIRTUAL_DATA_ADDRESS_START && memoryAddress <= VIRTUAL_DATA_ADDRESS_END)
		    {
		        memoryAddress -= DATA_OFFSET;
		        printMemoryCell(&EXECUTOR->memoryManager->stackMemory[memoryAddress/4], EXECUTOR->logger);
		        return;
		    }
			break;

		case PRINT_PROGRAM_MEMORY:
			printProgramMemory(EXECUTOR->memoryManager);
			break;

		case PRINT_STACK_MEMORY:
			printStackMemory(EXECUTOR->memoryManager);
			break;

		case PRINT_DATA_MEMORY:
			printDataMemory(EXECUTOR->memoryManager);
			break;

		case PRINT_REGISTER:

			break;

		case PRINT_REGISTER_FILE:
			printRegisterFile(EXECUTOR->registerFile);
			break;

		default:
			perror("Unkown instruction found!\n");
			break;
	}

}
