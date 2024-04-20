#include "instructions.h"
//------------------------------------------IMM------------------------------------------//


//------------------------------------------INSTRUCTION-MAP------------------------------------------//
typedef enum { R_TYPE, I_TYPE, S_TYPE, B_TYPE, U_TYPE, J_TYPE } InstructionType;

struct InstructionEncoding 
{
  InstructionType type;
  bool opcode[7];
  bool funct3[3];
  bool funct7[7];
};

map<string, int> labels;

map<string, InstructionEncoding> instruction_map = 
{
    // R-type
    {"add", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"sub", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 0, 0}, {0, 1, 0, 0, 0, 0, 0}}},
    {"sll", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 0, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    {"slt", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 1, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"sltu", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 1, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    {"xor", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {1, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"srl", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {1, 0, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    {"or", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {1, 1, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"and", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {1, 1, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    // I-type
    {"jalr", {I_TYPE, {1, 1, 0, 0, 1, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"lw", {I_TYPE, {0, 0, 0, 0, 0, 1, 1}, {0, 1, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"addi", {I_TYPE, {0, 0, 1, 0, 0, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"sltiu",
     {I_TYPE, {0, 0, 1, 0, 0, 1, 1}, {0, 1, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    // S-type
    {"sw", {S_TYPE, {0, 1, 0, 0, 0, 1, 1}, {0, 1, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    // B-type
    {"beq", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"bne", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {0, 0, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    {"blt", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {1, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"bge", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {1, 0, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    {"bltu", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {1, 1, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"bgeu", {B_TYPE, {1, 1, 0, 0, 0, 1, 1}, {1, 1, 1}, {0, 0, 0, 0, 0, 0, 0}}},
    // U-type
    {"lui", {U_TYPE, {0, 1, 1, 0, 1, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"auipc",
     {U_TYPE, {0, 0, 1, 0, 1, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    // J-type
    {"jal", {J_TYPE, {1, 1, 0, 1, 1, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
};
//--------------------------------------------------------------------------------------------------//

//------------------------------------------REGISTER-MAP------------------------------------------//

struct RegisterEncoding 
{
  string name;
  bool address[5];
  char saver_status;
  // 0 -Caller
  // 1 -Callee
  // 2 -None
};

map<string, RegisterEncoding> register_map = 
{

    {"zero", {"x0", {0, 0, 0, 0, 0}, 2}}, {"ra", {"x1", {0, 0, 0, 0, 1}, 0}},
    {"sp", {"x2", {0, 0, 0, 1, 0}, 1}},   {"gp", {"x3", {0, 0, 0, 1, 1}, 2}},
    {"tp", {"x4", {0, 0, 1, 0, 0}, 2}},   {"t0", {"x5", {0, 0, 1, 0, 1}, 0}},
    {"t1", {"x6", {0, 0, 1, 1, 0}, 0}},   {"t2", {"x7", {0, 0, 1, 1, 1}, 0}},
    {"s0", {"x8", {0, 1, 0, 0, 0}, 1}},   {"fp", {"x8", {0, 1, 0, 0, 0}, 1}},
    {"s1", {"x9", {0, 1, 0, 0, 1}, 1}},   {"a0", {"x10", {0, 1, 0, 1, 0}, 0}},
    {"a1", {"x11", {0, 1, 0, 1, 1}, 0}},  {"a2", {"x12", {0, 1, 1, 0, 0}, 0}},
    {"a3", {"x13", {0, 1, 1, 0, 1}, 0}},  {"a4", {"x14", {0, 1, 1, 1, 0}, 0}},
    {"a5", {"x15", {0, 1, 1, 1, 1}, 0}},  {"a6", {"x16", {1, 0, 0, 0, 0}, 0}},
    {"a7", {"x17", {1, 0, 0, 0, 1}, 0}},  {"s2", {"x18", {1, 0, 0, 1, 0}, 0}},
    {"s3", {"x19", {1, 0, 0, 1, 1}, 0}},  {"s4", {"x20", {1, 0, 1, 0, 0}, 0}},
    {"s5", {"x21", {1, 0, 1, 0, 1}, 0}},  {"s6", {"x22", {1, 0, 1, 1, 0}, 0}},
    {"s7", {"x23", {1, 0, 1, 1, 1}, 0}},  {"s8", {"x24", {1, 1, 0, 0, 0}, 0}},
    {"s9", {"x25", {1, 1, 0, 0, 1}, 0}},  {"s10", {"x26", {1, 1, 0, 1, 0}, 0}},
    {"s11", {"x27", {1, 1, 0, 1, 1}, 0}}, {"t3", {"x28", {1, 1, 1, 0, 0}, 0}},
    {"t4", {"x29", {1, 1, 1, 0, 1}, 0}},  {"t5", {"x30", {1, 1, 1, 1, 0}, 0}},
    {"t6", {"x31", {1, 1, 1, 1, 1}, 0}},
};

vector<bool> int_to_signed_bin_array(int a, int n) 
{
  // Check if the number is within the range
  int max_positive = (1 << (n - 1)) - 1;
  int min_negative = -(1 << (n - 1));

  if (a > max_positive || a < min_negative) 
  {
    // Handle the error case
    throw out_of_range("Number out of range for the given bit size");
  }

  vector<bool> bin_array(n);
  uint32_t value =
      (a < 0) ? static_cast<uint32_t>(-a) : static_cast<uint32_t>(a);

  // Handle negative numbers using two's complement
  if (a < 0) 
  {
    value = ~value + 1;
  }

  for (int i = 0; i < n; i++) 
  {
    bin_array[i] = (value & (1 << (n - 1 - i))) ? 1 : 0;
  }

  return bin_array;
}

vector<bool> slice_bool_array(const vector<bool> &bool_array, int start_index, int end_index) 
{
  // Create a new vector to hold the sliced elements
  vector<bool> sliced_array;

  // Iterate over the desired range and copy elements to the new vector
  for (int i = start_index; i < end_index + 1; ++i) 
  {
    sliced_array.push_back(bool_array[i]);
  }

  return sliced_array;
}
//----------------------------------------------------------------------------------------------------------//
//-----------------------------------------TOKENIZER------------------------------------------//
vector<string> tokenize(const string &line, int line_number) 
{
  vector<string> tokens;
  stringstream ss(line);
  string token;

  // Tokenize based on spaces and colons
  while (getline(ss, token, ' ')) 
  {
    // Remove leading and trailing whitespace
    token.erase(0, token.find_first_not_of(" \t\r\n"));
    token.erase(token.find_last_not_of(" \t\r\n") + 1);

    // Skip comments and blank lines
    if (token.empty() || token[0] == '/' || token[0] == '\n') 
    {
      continue;
    }

    // Check if the token is a label
    if (token.back() == ':') 
    {
      if (token.length() == 1) 
      {
        throw runtime_error("Error: Invalid label");
        continue;
      }
      labels.insert({token.substr(0, token.length() - 1), line_number});
      // tokens.push_back(token.substr(
      // 0, token.length() - 1)); // Add the label without the colon
      continue; // Skip to the next token
    }

    // Tokenize based on commas
    stringstream subss(token);
    string subToken;
    vector<vector<vector<string>>> subTokens;

    while (getline(subss, subToken, ',')) 
    {
      vector<vector<string>> subSubTokens;
      stringstream subSubss(subToken);
      string subSubToken;

      // Tokenize based on opening parentheses
      while (getline(subSubss, subSubToken, '(')) 
      {
        vector<string> subSubSubTokens;
        stringstream subSubSubss(subSubToken);
        string subSubSubToken;

        // Tokenize based on closing parentheses
        while (getline(subSubSubss, subSubSubToken, ')')) 
        {
          subSubSubTokens.push_back(subSubSubToken);
        }
        subSubTokens.push_back(subSubSubTokens);
      }
      subTokens.push_back(subSubTokens);
    }

    // Flatten the nested vector structure
    for (const auto &outerToken : subTokens) 
    {
      for (const auto &innerToken : outerToken) 
      {
        for (const auto &subInnerToken : innerToken) 
        {
          tokens.push_back(subInnerToken);
        }
      }
    }
  }

  return tokens;
}

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------DECODER------------------------------------------//

vector<bool> decode(vector<string> tokens, int line_number) 
{

  vector<bool> decoded(32);
  static const regex integer_regex("^-?\\d+$");

  // if (tokens.empty()) {
  //   cerr << "Error: Empty instruction " << endl;
  //   return decoded;
  // }
  // if (instruction_map.find(tokens[0]) == instruction_map.end()) {
  //   cerr << "Error: Unknown instruction '" << tokens[0] << endl;
  //   return decoded;
  // }
  InstructionType type = instruction_map[tokens[0]].type;

  if (type == R_TYPE) 
  {

    if (tokens.size() != 4) 
    {
      throw runtime_error("Error: Invalid number of operands for R-type instrucion " + (tokens[0]));
    }

    if (register_map.find(tokens[1]) == register_map.end() ||
        register_map.find(tokens[2]) == register_map.end() ||
        register_map.find(tokens[3]) == register_map.end()) 
    {
      throw runtime_error("Error: Invalid register operand for instruction '" + (tokens[0]));
    }
    // funct7
    for (int i = 0; i < 7; ++i) 
    {
      decoded[i] = instruction_map[tokens[0]].funct7[i];
    }
    // rs2
    for (int i = 0; i < 5; ++i) 
    {
      decoded[i + 7] = register_map[tokens[3]].address[i];
    }
    // rs1
    for (int i = 0; i < 5; ++i) 
    {
      decoded[i + 12] = register_map[tokens[2]].address[i];
    }
    // funct3
    for (int i = 0; i < 3; ++i) 
    {
      decoded[i + 17] = instruction_map[tokens[0]].funct3[i];
    }
    // rd
    for (int i = 0; i < 5; ++i) 
    {
      decoded[i + 20] = register_map[tokens[1]].address[i];
    }
    // opcode
    for (int i = 0; i < 7; ++i) 
    {
      decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
    }

  } 
  else if (type == I_TYPE) 
  {

    if (tokens.size() != 4) 
    {
      throw runtime_error("Error: Invalid number of operands for I-type instruction: " + (tokens[0]));
    }

    if (tokens[0] == "lw") 
    {
      if (register_map.find(tokens[1]) == register_map.end() ||
          register_map.find(tokens[3]) == register_map.end()) 
      {
        throw runtime_error("Error: Invalid register operand for instruction: " + (tokens[0]));
      }
    }

    if (tokens[0] != "lw") 
    {
      if (register_map.find(tokens[1]) == register_map.end() ||
          register_map.find(tokens[2]) == register_map.end()) 
      {
        throw runtime_error("Error: Invalid register operand for instruction: " + (tokens[0]));
      }
    }

    if (tokens[0] == "lw") 
    {
      if (!regex_match(tokens[2], integer_regex)) 
      {
        throw runtime_error("Error: Invalid immediate value: " + (tokens[3]) + " " + (tokens[0]));
      }
    }

    if (tokens[0] != "lw") 
    {
      if (!regex_match(tokens[3], integer_regex)) 
      {
        throw runtime_error("Error: Invalid immediate value: " + (tokens[3]) + " " + (tokens[0]));
      }
    }

    if (tokens[0] == "lw") 
    {
      // imm
      vector<bool> imm = int_to_signed_bin_array(stoi(tokens[2]), 12);
      for (int i = 0; i < 12; ++i) {
        decoded[i] = imm[i];
      }
      // rs1
      for (int i = 0; i < 5; ++i) 
      {
        decoded[i + 12] = register_map[tokens[3]].address[i];
      }
      // funct3
      for (int i = 0; i < 3; ++i) 
      {
        decoded[i + 17] = instruction_map[tokens[0]].funct3[i];
      }
      // rd
      for (int i = 0; i < 5; ++i) 
      {
        decoded[i + 20] = register_map[tokens[1]].address[i];
      }
      // opcode
      for (int i = 0; i < 7; ++i) 
      {
        decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
      }
    } 
    else 
    {
      // imm
      vector<bool> imm = int_to_signed_bin_array(stoi(tokens[3]), 12);
      for (int i = 0; i < 12; ++i) 
      {
        decoded[i] = imm[i];
      }
      // rs1
      for (int i = 0; i < 5; ++i) 
      {
        decoded[i + 12] = register_map[tokens[2]].address[i];
      }
      // funct3
      for (int i = 0; i < 3; ++i) 
      {
        decoded[i + 17] = instruction_map[tokens[0]].funct3[i];
      }
      // rd
      for (int i = 0; i < 5; ++i) 
      {
        decoded[i + 20] = register_map[tokens[1]].address[i];
      }
      // opcode
      for (int i = 0; i < 7; ++i) 
      {
        decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
      }
    }

  } 
  else if (type == S_TYPE) 
  {

    if (tokens.size() != 4) 
    {
      throw runtime_error("Error: Invalid number of operands for I-Type instruction: " + (tokens[0]));
    }

    if (register_map.find(tokens[1]) == register_map.end() ||
        register_map.find(tokens[3]) == register_map.end()) 
    {
      throw runtime_error("Error: Invalid register operand for instruction: " + (tokens[0]));
    }

    if (!regex_match(tokens[2], integer_regex)) 
    {
      throw runtime_error("Error: Invalid immediate value: " + (tokens[3]) + " " + (tokens[0]));
    }

    // imm[11:5]
    vector<bool> imm_11_5 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 12), 0, 6);
    for (int i = 0; i < 7; ++i) 
    {
      decoded[i] = imm_11_5[i];
    }
    // rs2
    for (int i = 0; i < 5; ++i) 
    {
      decoded[i + 7] = register_map[tokens[1]].address[i];
    }
    // rs1
    for (int i = 0; i < 5; ++i) 
    {
      decoded[i + 12] = register_map[tokens[3]].address[i];
    }
    // funct3
    for (int i = 0; i < 3; ++i) 
    {
      decoded[i + 17] = instruction_map[tokens[0]].funct3[i];
    }
    // imm[4:0]
    vector<bool> imm_4_0 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 12), 7, 11);
    for (int i = 0; i < 5; ++i) 
    {
      decoded[i + 20] = imm_4_0[i];
    }
    // opcode
    for (int i = 0; i < 7; ++i) 
    {
      decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
    }

  } 
  else if (type == B_TYPE) 
  {

    if (tokens.size() != 4) 
    {
        throw runtime_error("Error: Invalid number of operands for B-Type instruction: " + (tokens[0]));
    }

    for (auto &label : labels) 
    {
      if (tokens[3] == label.first) 
      {
        tokens[3] = (line_number - label.second);
        cerr << tokens[3] << endl;
      }
    }
    if (register_map.find(tokens[1]) == register_map.end()) 
    {
      throw runtime_error("Error: Invalid register operand for instruction: " + (tokens[0]));
    }

    if (!regex_match(tokens[3], integer_regex)) 
    {
      throw runtime_error("Error: Invalid immediate value: " + (tokens[3]) + " " + (tokens[0]));
    }

    // imm[12]
    vector<bool> imm_12 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[3]), 16), 3, 3);
    for (int i = 0; i < 1; ++i) 
    {
      decoded[i] = imm_12[i];
    }
    // imm[10:5]
    vector<bool> imm_10_5 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[3]), 16), 5, 10);
    for (int i = 0; i < 6; ++i) 
    {
      decoded[i + 1] = imm_10_5[i];
    }
    // rs2
    for (int i = 0; i < 5; ++i) 
    {
      decoded[i + 7] = register_map[tokens[2]].address[i];
    }
    // rs1
    for (int i = 0; i < 5; ++i) 
    {
      decoded[i + 12] = register_map[tokens[1]].address[i];
    }
    // funct3
    for (int i = 0; i < 3; ++i) 
    {
      decoded[i + 17] = instruction_map[tokens[0]].funct3[i];
    }
    // imm[4:1]
    vector<bool> imm_4_1 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[3]), 16), 11, 14);
    for (int i = 0; i < imm_4_1.size(); ++i) 
    {
      decoded[i + 20] = imm_4_1[i];
    }
    // imm[11]
    vector<bool> imm_11 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[3]), 16), 4, 4);
    for (int i = 0; i < 1; ++i) 
    {
      decoded[i + 24] = imm_11[i];
    }
    // opcode
    for (int i = 0; i < 7; ++i) 
    {
      decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
    }

  } 
  else if (type == U_TYPE) 
  {

    if (tokens.size() != 3) 
    {
      throw runtime_error("Error: Invalid number of operands for U type: " + (tokens[0]));
    }

    if (register_map.find(tokens[1]) == register_map.end()) 
    {
      throw runtime_error("Error: Invalid register operand for instruction: " + (tokens[0]));
    }

    if (!regex_match(tokens[2], integer_regex)) 
    {
      throw runtime_error("Error: Invalid immediate value: " + (tokens[3]) + " " + (tokens[0]));
    }

    // imm[31:12]
    vector<bool> imm_31_12 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 32), 0, 19);
    for (int i = 0; i < 20; ++i) 
    {
      decoded[i] = imm_31_12[i];
    }
    // rd
    for (int i = 0; i < 5; ++i) 
    {
      decoded[i + 20] = register_map[tokens[1]].address[i];
    }
    // opcode
    for (int i = 0; i < 7; ++i) 
    {
      decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
    }

  } else if (type == J_TYPE) {
    if (tokens.size() != 3) {
      throw runtime_error("Error: Invalid number of operands for instruction :" + (tokens[0]));
    }

    for (auto &label : labels) {
      if (tokens[2] == label.first) {
        tokens[2] = (line_number - label.second);
      }
    }
    if (register_map.find(tokens[1]) == register_map.end()) {
      throw runtime_error("Error: Invalid number of operands for instruction :" + (tokens[0]));
    }

    // if (!regex_match(tokens[2], integer_regex)) {
    //   cout << tokens[2] << endl;
    //   cerr << "Error: Invalid immediate value '" << tokens[2]
    //        << "' for instruction '" << tokens[0] << endl;
    //   exit(0);
    // }

    // imm[20]
    vector<bool> imm_20 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 21), 0, 0);
    for (int i = 0; i < 1; ++i) {
      decoded[i] = imm_20[i];
    }
    // imm[10:1]
    vector<bool> imm_10_1 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 21), 10, 19);
    for (int i = 0; i < 10; ++i) {
      decoded[i + 1] = imm_10_1[i];
    }
    // imm[11]
    // dikkat
    vector<bool> imm_11 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 21), 9, 9);
    for (int i = 0; i < 1; ++i) {
      decoded[i + 11] = imm_11[i];
    }
    // imm[19:12]
    vector<bool> imm_19_12 =
        slice_bool_array(int_to_signed_bin_array(stoi(tokens[2]), 21), 1, 8);
    for (int i = 0; i < 8; ++i) {
      decoded[i + 12] = imm_19_12[i];
    }
    // rd
    for (int i = 0; i < 5; ++i) {
      decoded[i + 20] = register_map[tokens[1]].address[i];
    }
    // opcode
    for (int i = 0; i < 7; ++i) {
      decoded[i + 25] = instruction_map[tokens[0]].opcode[i];
    }
  } else {
      throw runtime_error("Error: Invalid instruction");
  }

  return decoded;
}
//----------------------------------------------------------------------------------------------------------//

//-------------------------------------------FILE
// READER-------------------------------------------//

void asseble(const string& input_file_name, const string& output_file_name) 
{
    ifstream input_file(input_file_name);
    ofstream output_file(output_file_name);
    string line;

    if (!input_file.is_open()) {
        throw runtime_error("Error: Unable to open input file :" + input_file_name);
    }

    if (!output_file.is_open()) {
      throw runtime_error("Error: Unable to open output file :" + output_file_name);
    }

    int line_number = 1;
    while (getline(input_file, line)) {
        vector<string> tokens = tokenize(line, line_number);
        vector<bool> decoded = decode(tokens, line_number);
        for (int i = 0; i < 32; ++i) {
            output_file << decoded[i];
        }
        output_file << endl;
        line_number++;
    }

    input_file.close();
    output_file.close();
}

//-------------------------------------------------MAIN-------------------------------------------------//