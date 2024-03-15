#include "RTypeExecutor.h"
#include <stdlib.h>
// - - - - - - - - - - - - - -

rTypeExecutor* initialiseRTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    rTypeExecutor* executor = (rTypeExecutor*)malloc(sizeof(rTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    executor->programCounter = PROGRAM_COUNTER;
    return executor;
}

// - - - - - - - - - - - - -

void destroyRTypeExecutor(rTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -

void add_sub(Register* RD, Register* RS1, Register* RS2, bool IS_SUB)
{
    short rs1 = signExtend(RS1->bits, REGISTER_SIZE);
    short rs2 = signExtend(RS1->bits, REGISTER_SIZE);
    short answer = IS_SUB ? rs1 - rs2 : rs1 + rs2;
    Bit answerBits[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        answerBits[i].value = (answer >> i) & 1;
    }
    setRegisterValue(RD, answerBits);
}

// - - - - - - - - - - - - -

void slt(Register* RD, Register* RS1, Register* RS2, bool IS_SIGNED)
{
    short rs1 = toDecimal(RS1->bits, 0, REGISTER_SIZE, false);
    short rs2 = toDecimal(RS2->bits, 0, REGISTER_SIZE, false);

    if (IS_SIGNED)
    {
        rs1 = signExtend(RS1->bits, REGISTER_SIZE);
        rs2 = signExtend(RS1->bits, REGISTER_SIZE);
    }

    short answer = rs1 << rs2;
    Bit answerBits[REGISTER_SIZE];

    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        answerBits[i].value = (answer >> i) & 1;
    }

    setRegisterValue(RD, answerBits);
}

// - - - - - - - - - - - - -

void bitwiseXor(Register* RD, Register* RS1, Register* RS2)
{
    Bit answer[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        answer[i].value = RS1->bits[i].value ^ RS2->bits[i].value;
    }
    setRegisterValue(RD, answer);
};

// - - - - - - - - - - - - -

void bitwiseOr(Register* RD, Register* RS1, Register* RS2)
{
    Bit answer[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        answer[i].value = RS1->bits[i].value | RS2->bits[i].value;
    }
    setRegisterValue(RD, answer);
};

// - - - - - - - - - - - - -

void bitwiseAnd(Register* RD, Register* RS1, Register* RS2)
{
    Bit answer[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        answer[i].value = RS1->bits[i].value & RS2->bits[i].value;
    }
    setRegisterValue(RD, answer);
}

// - - - - - - - - - - - - -

void shiftBits(Register* RD, Register* RS1, Register* RS2, bool SHIFT_LEFT)
{
    unsigned int rs1 = toDecimal(RS1->bits, 0, REGISTER_SIZE, false);
    unsigned int rs2 = toDecimal(RS2->bits, 0, SHIFT_LIMIT, false);
    unsigned int answer = SHIFT_LEFT ? rs1 << rs2 : rs1 >> rs2;
    Bit answerBits[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        answerBits[i].value = (answer >> (REGISTER_SIZE - 1 - i)) & 1;
    }
    setRegisterValue(RD, answerBits);
}

// - - - - - - - - - - - - -

// - - - - - - - - - - - - -

void executeRTypeInstruction(rTypeExecutor *EXECUTOR, Bit *Instruction)
{
    char funct3 = toDecimal(Instruction, FUNCT3_START, FUNCT3_END, false);
    char funct7 = toDecimal(Instruction, FUNCT7_START, FUNCT7_END, false); 
    char rd = toDecimal(Instruction, RD_START, RD_END, false);
    char rs1 = toDecimal(Instruction, RS1_START, RS1_END, false);
    char rs2 = toDecimal(Instruction, RS2_START, RS2_END, false);
    //Simulator manages only run time errors
    //THis is an assemble time error and will not be handled by the simulator
    
    switch(funct3)
    {
        case ADD_SUB:
            switch(funct7)
            {
                case ADD:
                    add_sub(&EXECUTOR->registerFile->registers[rd], &EXECUTOR->registerFile->registers[rs1], &EXECUTOR->registerFile->registers[rs2], false);
                    break;
                case SUB:
                    add_sub(&EXECUTOR->registerFile->registers[rd], &EXECUTOR->registerFile->registers[rs1], &EXECUTOR->registerFile->registers[rs2], true);
                    break;
                default:
                    break;
            }

        case SLT:
            slt(&EXECUTOR->registerFile->registers[rd], &EXECUTOR->registerFile->registers[rs1], &EXECUTOR->registerFile->registers[rs2], false);
            break;

        case SLTU:
            slt(&EXECUTOR->registerFile->registers[rd], &EXECUTOR->registerFile->registers[rs1], &EXECUTOR->registerFile->registers[rs2], true);
            break;

        case XOR:
            bitwiseXor(&EXECUTOR->registerFile->registers[rd], &EXECUTOR->registerFile->registers[rs1], &EXECUTOR->registerFile->registers[rs2]);
            break;

        case OR:
            bitwiseOr(&EXECUTOR->registerFile->registers[rd], &EXECUTOR->registerFile->registers[rs1], &EXECUTOR->registerFile->registers[rs2]);
            break;

        case AND:
            bitwiseAnd(&EXECUTOR->registerFile->registers[rd], &EXECUTOR->registerFile->registers[rs1], &EXECUTOR->registerFile->registers[rs2]);
            break;

        case SLL:
            shiftBits(&EXECUTOR->registerFile->registers[rd], &EXECUTOR->registerFile->registers[rs1], &EXECUTOR->registerFile->registers[rs2], true);
            break;

        case SRL:
            shiftBits(&EXECUTOR->registerFile->registers[rd], &EXECUTOR->registerFile->registers[rs1], &EXECUTOR->registerFile->registers[rs2], false);
            break;

    }
}


