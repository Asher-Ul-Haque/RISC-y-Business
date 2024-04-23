#ifndef IO_TYPE_EXECUTOR
#define IO_TYPE_EXECUTOR
#ifdef __cplusplus
extern "C"{
#endif

#include "../../../memory/memory.h"
// - - - - - - - - - -
#define INSTRUCTION_SIZE 32
// - - - - - - - - - -
#define FUNCT3_SIZE 3
#define FUNCT3_START 7
#define FUNCT3_END FUNCT3_START + FUNCT3_SIZE
#define PRINT_MEMORY_CELL 0
#define PRINT_PROGRAM_MEMORY 1
#define PRINT_STACK_MEMORY 2
#define PRINT_DATA_MEMORY 3
#define PRINT_REGISTER 4
#define PRINT_REGISTER_FILE 5
#define SCAN 6
// - - - - - - - - - -
#define VIRTUAL_DATA_ADDRESS_START 65536
#define VIRTUAL_DATA_ADDRESS_END 131071
#define VIRTUAL_STACK_ADDRESS_START 256
#define VIRTUAL_STACK_ADDRESS_END 383
#define STACK_OFFSET 64
#define DATA_OFFSET 16384
#define SCALE_FACTOR 4
// - - - - - - - - - - - -
#define RD_START FUNCT3_END
#define RD_END RD_START + REGISTER_ADDRESS_SIZE
#define MEMORY_START FUNCT3_END
#define MEMORY_END MEMORY_START + ADDRESS_SIZE
// - - - - - - -- - 
#define IMMEDIATE_START RD_END
#define IMMEDIATE_SIZE 12
#define IMMEDIATE_END IMMEDIATE_START + IMMEDIATE_SIZE

typedef struct 
{
	Memory* memoryManager;
	RegisterFile* registerFile;
	Logger* logger;
} ioTypeExecutor;

// - - - - - - - - - - 

ioTypeExecutor* initialiseIOTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, Logger* LOGGER);

void destroyIOTypeExecutor(ioTypeExecutor* EXECUTOR);

void executeIOTypeInstruction(ioTypeExecutor* EXECUTOR, Bit INSTRUCTION[INSTRUCTION_SIZE]);

// - - - - - - - -
#ifdef __cplusplus
}
#endif //extern "C"

#endif //IO_TYPE_INSTRUCTION