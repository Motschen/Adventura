#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <streambuf>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string readInput(string feedback);
string readFile(const string& fileLocation);

/**
 * Reads a string from the user. The string is expected to be the first
 * argument before a comma.
 *
 * @return The string read from the user.
 */
string readInput(string feedback) {
  string name;
  cout << feedback << endl;
  getline(std::cin, name);
  return name;
}

string readFile(const string& fileLocation) {
  std::ifstream ifs(fileLocation);
  return string((std::istreambuf_iterator <char>( ifs )),
    (std::istreambuf_iterator<char >()));
}
vector<string> readFileAsVector(const string& fileLocation) {
  string rawFile = readFile(fileLocation);
  vector<string> file; 
  string currentLine = "";
  for (char c : rawFile) {
    if (c == '\n' || c == '\r') {
      file.push_back(currentLine);
      currentLine = "";
    }
    else {
      currentLine += c;
    }
  }
  file.push_back(currentLine);
  return file;
}