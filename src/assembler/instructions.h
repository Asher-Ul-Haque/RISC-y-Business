#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "bits/stdc++.h"
#include "iostream"
#include "sstream"
#include "string"
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

vector<bool> int_to_signed_bin_array(int a, int n);

vector<bool> slice_bool_array(const vector<bool> &bool_array, int start_index, int end_index);

vector<string> tokenize(const string &line, int line_number);

vector<bool> decode(vector<string> tokens, int line_number);

void asseble(const string& input_file_name, const string& output_file_name); 

#endif //INSUTRCTIONS_H