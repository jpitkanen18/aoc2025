#pragma once
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
static StringVector LoadFile(int argc, char* argv[]) {
  std::string filePath = "testinput.txt";
  bool part2 = true;

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

static void PrintInput(StringVector input) {
  for (const auto a : input) {
    std::cout << a << '\n';
  }
}

static Vec2 CoordsFromSmatch(std::smatch& m) {
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

static Vec2 Vec2FromRegex(std::string& input, std::regex& r) {
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
