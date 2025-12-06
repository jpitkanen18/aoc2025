#include <iostream>
#include <map>

#include "../utils/Timer.hpp"
#include "../utils/Types.hpp"
#include "../utils/Utils.hpp"

bool part2 = false;

class MathCalculator {
  using Operation = std::pair<char, std::vector<int>>;
  std::vector<Operation> operations;

 public:
  MathCalculator(StringVector& input) {
    int offset = 0;
    if (!part2) {
      for (int i = 1; i <= input[0].size(); i++) {
        if (i == input[0].size() || (input[0][i] == ' ' &&
                                     input[1][i] == ' ' &&
                                     input[2][i] == ' ' &&
                                     input[3][i] == ' ' &&
                                     input[3][i] == ' ')) {
          Operation op;
          op.first = input[3][offset];
          std::string temp;
          for (int j = 0; j < 3; j++) {
            temp = {input[j].begin() + (i - (i - offset)), input[j].begin() + i};
            op.second.push_back(stoi(temp));
          }
          operations.push_back(op);
          offset = i + 1;
        }
      }
    } else {
      for (int i = 1; i <= input[0].size(); i++) {
        if (i == input[0].size() || (input[0][i] == ' ' &&
                                     input[1][i] == ' ' &&
                                     input[2][i] == ' ' &&
                                     input[3][i] == ' ' &&
                                     input[4][i] == ' ')) {
          Operation op;
          op.first = input[4][offset];
          std::string temp;
          for (int j = offset; j < i; j++) {
            temp = {
                input[0][j],
                input[1][j],
                input[2][j],
                input[3][j]};
            std::cout << "Temp: " << temp << '\n';
            op.second.push_back(stoi(temp));
            temp.clear();
          }
          operations.push_back(op);
          offset = i + 1;
        }
      }
    }
  }

  long GetOperationsTotal() {
    long total = 0;
#pragma omp parallel for reduction(+ : total)
    for (const auto op : operations) {
      long subtotal = 0;
      for (const auto num : op.second) {
        if (op.first == '*')
          subtotal = subtotal == 0 ? num : subtotal * num;
        else if (op.first == '+')
          subtotal += num;
      }
      total += subtotal;
    }
    return total;
  }
};

int main(int argc, char* argv[]) {
  StringVector input = Utils::LoadFile(argc, argv, part2);

  Timer timer = Timer();
  timer.Start();

  MathCalculator mCalculator(input);

  std::cout << "Operations total: " << mCalculator.GetOperationsTotal() << '\n';

  timer.End();

  return 0;
}
