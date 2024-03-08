//
// Created by Divyanshu on 08-03-2024.
//

#ifndef RISC_Y_BUSINESS_MAIN_INSTRUCTIONS_H
#define RISC_Y_BUSINESS_MAIN_INSTRUCTIONS_H

#include "iostream"
#include "bits/stdc++.h"
#include <map>
#include <vector>
#include "sstream"
#include "string"

//------------------------------------------INSTRUCTION MAP--------------------------------------------//
typedef enum {
    R_TYPE,
    I_TYPE,
    S_TYPE,
    B_TYPE,
    U_TYPE,
    J_TYPE
} InstructionType;

struct InstructionEncoding {
    InstructionType type;
    bool opcode[7];
    bool funct3[3];
    bool funct7[7];
};

std::map<std::string, InstructionEncoding> instruction_map;

//------------------------------------------REGISTER MAP--------------------------------------------//


struct RegisterEncoding {
    std::string name;
    bool address[5];
    char  saver_status;
    // 0 -Caller
    // 1 -Callee
    // 2 -None
};

std::map<std::string,RegisterEncoding> register_map;

//------------------------------------------IMM--------------------------------------------//

std::vector<bool> int_to_signed_bin_array(int a, int n);

std::vector<bool> slice_bool_array(const std::vector<bool>& bool_array, int start_index, int end_index);

//------------------------------------------TOKENIZER--------------------------------------------//

std::vector<std::string> tokenize(const std::string& line);

//------------------------------------------INSTRUCTION DECODER--------------------------------------------//

std::vector<bool> decode(std::vector<std::string> tokens);

//------------------------------------------FILE READER--------------------------------------------//

void read_file(const std::string& file_name);

#endif //RISC_Y_BUSINESS_MAIN_INSTRUCTIONS_H
