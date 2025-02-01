#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include <filesystem>
#include <algorithm>

#include "color.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string readInput(string feedback);

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

/**
 * Get a list of all files in the specified directory, sorted alphabetically.
 *
 * This is used to progress through the worlds in the correct order.
 * 
 * @param dir The directory to get the file names from
 * @param extension The file extension to filter by
 * @return A list of all file names in the specified directory, sorted alphabetically.
 */
vector<string> getOrderedFileNames(string dir, string extension) {
    vector<string> worlds;
    // This used to be so elegant and iterate over all files in the worlds directory,
    // but because of the weird restriction with no folders being allowed, we just filter the files based on their extension.
    for (auto & entry : std::filesystem::directory_iterator(dir)) {
        if (static_cast<string>(entry.path()).ends_with(extension)) worlds.push_back(entry.path());
    }
    // We use this to sort the worlds alphabetically, so that the game progresses in the correct order.
    std::sort( worlds.begin(), worlds.end(), [](string a, string b) {
        return a < b;
    });
    return worlds;
}

/**
 * Reads the given file and returns its content as a vector of strings.
 * Each string represents a line in the file.
 *
 * @param fileLocation The location of the file to read.
 * @return The content of the file as a vector of strings.
 */
vector<string> readFileAsVector(const string& fileLocation) {
  
  vector<string> lines; 
  // string currentLine = "";
  // for (char c : readFile(fileLocation)) {
  //   if (c == '\n' || c == '\r') {
  //     file.push_back(currentLine);
  //     currentLine = "";
  //   }
  //   else {
  //     currentLine += c;
  //   }
  // }
  // file.push_back(currentLine);

  std::ifstream file(fileLocation);
  // Read the file line by line into a string
  string line;
  while (std::getline(file, line)) {
      lines.push_back(line);
  }
  file.close();
  return lines;
}

/**
 * Prints the content of a file line by line into the console (in the specified color).
 * We use this to print our death and victory screens.
 *
 * @param fileLocation Path to the file to be printed.
 * @param color Color to be used for the output.
 */
void printFile(string fileLocation, Color color) {
    cout << color;
    vector<string> file = readFileAsVector(fileLocation);
    for (unsigned int y = 0; y < file.size(); y++) {
        cout << file.at(y) << endl;
    }
}