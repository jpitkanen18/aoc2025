#include <iostream>

#include "../utils/Timer.hpp"
#include "../utils/Types.hpp"
#include "../utils/Utils.hpp"

bool part2 = false;

class ForkliftOptimizer {
  StringVector input;
  StringVector mutableInput;

  long nPaperRolls = 0;

  const std::vector<Vec2> positions = {
      Vec2(0, -1),
      Vec2(1, -1),
      Vec2(1, 0),
      Vec2(1, 1),
      Vec2(0, 1),
      Vec2(-1, 1),
      Vec2(-1, 0),
      Vec2(-1, -1)};

 public:
  ForkliftOptimizer(StringVector& input) {
    this->input = input;
    this->mutableInput = input;
  }

  bool CheckAdjacentPositions(int x, int y, StringVector& inputToCheck) {
    int hits = 0;
#pragma omp parallel for (+ : hits)
    for (const auto pos : positions) {
      int dx = x + pos.x;
      // Quick and dirty heuristic lool
      if (dx < 0 || dx >= inputToCheck[0].size()) {
        continue;
      }
      int dy = y + pos.y;
      if (dy < 0 || dy >= inputToCheck.size()) {
        continue;
      }

      if (inputToCheck[dy][dx] == '@')
        hits++;
    }
    bool fewer = hits < 4;
    if (fewer)
      mutableInput[y][x] = 'x';
    return fewer;
  }

  void OptimisePositions() {
#pragma omp parallel for reduction(+ : nPaperRolls)
    for (int y = 0; y < input.size(); y++) {
      for (int x = 0; x < input[y].size(); x++) {
        if (input[y][x] == '@') {
          if (CheckAdjacentPositions(x, y, input)) {
            nPaperRolls++;
          }
        }
      }
    }
  }

  void OptimisePositionsV2() {
    while (true) {
      bool positionsFound = false;
      for (int y = 0; y < mutableInput.size(); y++) {
#pragma omp parallel for reduction(+ : nPaperRolls)
        for (int x = 0; x < mutableInput[y].size(); x++) {
          if (mutableInput[y][x] == '@') {
            if (CheckAdjacentPositions(x, y, mutableInput)) {
              nPaperRolls++;
              positionsFound = true;
            }
          }
        }
      }
      if (!positionsFound) {
        break;
      }
    }
  }

  long GetNumPaperRolls() {
    // Utils::PrintInput(mutableInput);
    return this->nPaperRolls;
  }
};

int main(int argc, char* argv[]) {
  StringVector input = Utils::LoadFile(argc, argv, part2);

  Timer timer = Timer();
  timer.Start();

  ForkliftOptimizer fOptimizer(input);
  if (!part2)
    fOptimizer.OptimisePositions();
  else
    fOptimizer.OptimisePositionsV2();

  std::cout << "Rolls optimized: "
            << fOptimizer.GetNumPaperRolls() << " rolls" << '\n';

  timer.End();

  return 0;
}
