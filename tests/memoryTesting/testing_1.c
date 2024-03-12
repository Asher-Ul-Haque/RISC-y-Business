#include "../../src/memory/memory.h"
#include "../../src/register/registers.h"
#include <stdio.h>

int main() {
    // Allocate memory
    Register stackPointer;
    Memory* memory = allocateMemory(&stackPointer);

    // Initialize a test register
    Register testRegister;
    Bit testBits[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i) {
        testBits[i].value = i % 2;  // Alternating 0s and 1s
    }
    setRegisterValue(&testRegister, testBits);
    printf("Test Register:\n");
    printRegister(&testRegister);

    // Test program memory access
    MemoryCell* programMemory = getProgramMemory(memory);
    printProgramMemory(memory);

    // Test stack memory operations
    printStackMemory(memory);
    printRegister(memory->stackPointer);
    printf("\n");
    pushStackMemory(memory, &testRegister);

    printf("After Push:\n");
    printStackMemory(memory);
    printRegister(memory->stackPointer);
    Bit* poppedBits = popStackMemory(memory);
    printf("After Pop:\n");
    printStackMemory(memory);
    printRegister(memory->stackPointer);
    // Test data memory access
    MemoryCell* dataMemory = getDataMemory(memory);
    printDataMemory(memory);

    // Deallocate memory
    deallocateMemory(memory);

    return 0;
}
