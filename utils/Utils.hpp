#pragma once
#include <bits/stdc++.h>

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "./Types.hpp"

namespace Utils {
inline StringVector LoadFile(int argc, char* argv[], bool& part2) {
  std::string filePath = "testinput.txt";

  if (argc > 1)
    filePath = argv[1];
  if (argc > 2 && strcmp(argv[2], "part2") == 0)
    part2 = true;

  std::ifstream test(filePath);

  if (!test) {
    printf("Did you forget to pass the filepath? ;D\n");
    throw std::exception();
  }

  std::ifstream inFile(filePath);
  StringVector fileAsString;

  if (inFile.is_open()) {
    inFile.clear();
    inFile.seekg(0, std::ios::beg);
    std::string line;
    while (std::getline(inFile, line)) {
      fileAsString.push_back(line);
    }
    inFile.close();
  }
  return fileAsString;
}

inline StringVector Split(std::string& input, std::string& delimiter) {
  StringVector splitted;
  std::string inputCopy(input);
  while (inputCopy.find(delimiter) != -1) {
    std::string token = inputCopy.substr(0, inputCopy.find(delimiter));
    splitted.push_back(token);
    inputCopy.erase(0, inputCopy.find(delimiter) + delimiter.length());
  }
  if (inputCopy.size() > 0) {
    splitted.push_back(inputCopy);
  }
  return splitted;
}

inline long FindAllCount(std::string& input, std::string& delimiter) {
  long count = 0;
  std::string inputCopy(input);
  while (inputCopy.find(delimiter) != -1) {
    std::string token = inputCopy.substr(0, inputCopy.find(delimiter));
    inputCopy.erase(0, inputCopy.find(delimiter) + delimiter.length());
    count++;
  }
  return count;
}

static long FindAllCount(std::string input, std::string delimiter) {
  long count = 0;
  std::string inputCopy(input);
  while (inputCopy.find(delimiter) != -1) {
    std::string token = inputCopy.substr(0, inputCopy.find(delimiter));
    inputCopy.erase(0, inputCopy.find(delimiter) + delimiter.length());
    count++;
  }
  return count;
}

template <typename T>
inline int IndexOf(std::vector<T>& vec, T& val, int startIndex = 0) {
  return distance(vec.begin(), find(vec.begin() + startIndex, vec.end(), val));
}

inline StringVector Split(std::string& input, const char* delimiter) {
  std::string delim(delimiter);
  return Split(input, delim);
}

inline void PrintInput(StringVector input) {
  for (const std::string& a : input) {
    std::cout << a << '\n';
  }
}

inline Vec2 CoordsFromSmatch(std::smatch& m) {
  std::regex r("-{0,1}\\d+");
  std::string input = m.str();

  Vec2* vec = (Vec2*)malloc(sizeof(Vec2));

  int j = 0;
  for (std::sregex_iterator i = std::sregex_iterator(input.begin(), input.end(), r);
       i != std::sregex_iterator();
       ++i) {
    std::smatch m = *i;
    long coord = atol(m.str().c_str());
    if (j == 0) {
      vec->x = coord;
    } else {
      vec->y = coord;
    }
    j++;
  }

  return *vec;
}

inline Vec2 Vec2FromRegex(std::string& input, std::regex& r) {
  Vec2* vec = (Vec2*)malloc(sizeof(Vec2));

  for (std::sregex_iterator i = std::sregex_iterator(input.begin(), input.end(), r);
       i != std::sregex_iterator();
       ++i) {
    std::smatch m = *i;
    *vec = CoordsFromSmatch(m);
  }

  return *vec;
}
};  // namespace Utils
