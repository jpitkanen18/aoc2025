#include <bits/stdc++.h>
#include <stdlib.h>

#include <iostream>

#include "../utils/Timer.hpp"
#include "../utils/Types.hpp"
#include "../utils/Utils.hpp"

bool part2 = false;

bool sorter(int i, int j) { return (i < j); }

class BatteryConfigurator {
  std::vector<std::vector<int>> batteryBanks;

 public:
  BatteryConfigurator(StringVector input) {
    for (std::string line : input) {
      std::vector<int> bank;
      for (char character : line) {
        bank.push_back((int)character - '0');
      }
      batteryBanks.push_back(bank);
    }
  }

  long GetMaxJoltage() {
    long totalJoltage = 0;
#pragma omp parallel for reduction(+ : totalJoltage)
    for (std::vector<int> bank : batteryBanks) {
      std::vector<int> copy(bank);
      std::string joltage;
      std::sort(copy.begin(), copy.end() - 1, sorter);
      joltage += (char)copy[0];
      int idx = Utils::IndexOf(bank, copy[0]) + 1;
      copy = {bank.begin() + idx, bank.end()};
      std::sort(copy.begin(), copy.end(), sorter);
      joltage += (char)copy[0];
      totalJoltage += stoi(joltage);
    }
    return totalJoltage;
  }

  std::string RecurseBanks(std::vector<int> bank, int idx, int minTail) {
    if (idx >= bank.size() || minTail < 0) {
      return "";
    }
    std::vector<int> copy(bank.begin() + idx, bank.end() - minTail);
    std::sort(copy.begin(), copy.end(), sorter);

    int largest = copy[copy.size() - 1];
    int largestIdx = Utils::IndexOf(bank, largest, idx);

    return std::to_string(largest) + this->RecurseBanks(bank, largestIdx + 1, minTail - 1);
  }

  long GetMaxJoltageV2() {
    long total = 0;
#pragma omp parallel for reduction(+ : total)
    for (std::vector<int> bank : batteryBanks) {
      std::string ans = this->RecurseBanks(bank, 0, 11);
      total += stol(ans);
    }
    return total;
  }
};

int main(int argc, char* argv[]) {
  StringVector input = Utils::LoadFile(argc, argv, part2);

  Timer timer = Timer();
  timer.Start();

  BatteryConfigurator bConfigurator(input);

  if (!part2)
    std::cout << "Total joltage: " << bConfigurator.GetMaxJoltage() << '\n';
  else
    std::cout << "Total joltage: " << bConfigurator.GetMaxJoltageV2() << '\n';

  timer.End();

  return 0;
}
