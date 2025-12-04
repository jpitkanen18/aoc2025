#include <iostream>
#include <string>

#include "../utils/Timer.hpp"
#include "../utils/Types.hpp"
#include "../utils/Utils.hpp"

bool part2 = false;

class ShopHelper {
  std::vector<std::pair<long, long>> parsedInput;

 public:
  ShopHelper(StringVector& input) {
    for (std::string line : input) {
      StringVector parsed = Utils::Split(line, ",");
      for (auto pair : parsed) {
        StringVector parsedPair = Utils::Split(pair, "-");
        this->parsedInput.push_back(std::pair(stol(parsedPair.at(0)), stol(parsedPair.at(1))));
      }
    }
  }

  long FilterIDs() {
    long total = 0;
#pragma omp parallel for reduction(+ : total)
    for (std::pair<long, long> range : parsedInput) {
      std::string val;
      for (long i = range.first; i <= range.second; i++) {
        val = std::to_string(i);
        if (val.size() % 2 != 0)
          continue;
        size_t half = val.size() / 2;
        if (val.substr(0, half) == val.substr(half)) {
          total += i;
        }
      }
    }
    return total;
  }

  long FilterIDsV2() {
    long total = 0;
#pragma omp parallel for reduction(+ : total)
    for (std::pair<long, long> range : parsedInput) {
      std::string val;
      for (long i = range.first; i <= range.second; i++) {
        val = std::to_string(i);
        size_t half = val.size() / 2;
        for (int j = 1; j <= half; j++) {
          if (Utils::FindAllCount(val, val.substr(0, j)) * j == val.size()) {
            total += i;
            break;
          }
        }
      }
    }
    return total;
  }
};

int main(int argc, char* argv[]) {
  StringVector input = Utils::LoadFile(argc, argv, part2);

  Timer timer = Timer();
  timer.Start();

  ShopHelper helper(input);
  long total = 0;
  if (!part2)
    total = helper.FilterIDs();
  else
    total = helper.FilterIDsV2();

  timer.End();

  std::cout << "Total: " << total << '\n';

  return 0;
}
