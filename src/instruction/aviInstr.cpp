#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// trim from end of string (right)
inline std::string &rtrim(std::string &s, const char *t = " \t\n\r\f\v") {
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}

// trim from beginning of string (left)
inline std::string &ltrim(std::string &s, const char *t = " \t\n\r\f\v") {
  s.erase(0, s.find_first_not_of(t));
  return s;
}

// trim from both ends of string (right then left)
inline std::string &trim(std::string &s, const char *t = " \t\n\r\f\v") {
  return ltrim(rtrim(s, t), t);
}

void tokenizer(string line, string tokenArray[], char del) {
  stringstream ss(line);
  string word;
  int i = 0;
  while (!ss.eof()) {
    getline(ss, word, del);
    tokenArray[i] = trim(word);
    i++;
  }
}

const int MAX_LINES = 1000;
const int MAX_LENGTH = 100;

string *readTextFile(const string &filename, int &numLines) {
  ifstream file(filename);
  if (!file.is_open()) {
    exit(EXIT_FAILURE);
  }

  string *lines = new string[MAX_LINES];
  string line;
  numLines = 0;

  while (getline(file, line) && numLines < MAX_LINES) {
    lines[numLines] = line;
    numLines++;
  }

  file.close();

  return lines;
}

int main() {
  // string s = "add r1, r2, r3";
  string tokens[5];
  // tokenizer(s, tokens, ' ');
  // for (int i = 0; i < 5; i++) {
  //   if (tokens[i] != "") {
  //     cout << tokens[i] << endl;
  //   }
  // }
  const string filename = "src/instruction/text.txt";

  int numLines;
  string *lines = readTextFile(filename, numLines);
  tokenizer(lines[0], tokens, ' ');
  tokenizer(tokens[1], tokens, ',');

  for (int i = 0; i < 5; i++) {
    if (tokens[i] != "") {
      cout << tokens[i] << endl;
    }
  }
  delete[] lines;
  return 0;
}
