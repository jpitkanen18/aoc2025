#include <iostream>

#include "../utils/Timer.hpp"
#include "../utils/Types.hpp"
#include "../utils/Utils.hpp"

bool part2 = false;

class SafeCracker {
  StringVector input;
  int dial = 50;
  int password = 0;

  void RotateDial(int by) {
    this->dial += by;
    if (this->dial > 99 || this->dial < 0) {
      int mod = this->dial % 100;
      if (mod < 0) {
        mod += 100;
      }
      if (part2) {
        int value = abs(this->dial / 100) + (mod == 0 ? -1 : 0);
        if (this->dial < 0 && this->dial - by != 0)
          value++;
        password += value;
      }
      this->dial = mod;
    }
    if (this->dial == 0) {
      password++;
    }
  }

 public:
  SafeCracker(StringVector input) {
    this->input = input;
  }

  void Crack() {
    // std ::cout << "The dial starts at: " << this->dial << '\n';
    for (const auto line : input) {
      char dir = line.at(0);
      int rotation = std::stoi(line.substr(1));
      if (dir == 'L') {
        RotateDial(-1 * rotation);
      } else {
        RotateDial(rotation);
      }
    }
  }

  int& GetPassword() {
    return this->password;
  }
};

int main(int argc, char* argv[]) {
  StringVector input = Utils::LoadFile(argc, argv, part2);

  Timer timer = Timer();
  timer.Start();
  SafeCracker sCracker(input);
  sCracker.Crack();
  timer.End();
  std::cout << "Password: " << sCracker.GetPassword() << '\n';

  return 0;
}
