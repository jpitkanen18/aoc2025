#if MULTITHREAD
#include <omp.h>
#endif

#include <iostream>
#include <ranges>
#include <set>

#include "../utils/Timer.hpp"
#include "../utils/Types.hpp"
#include "../utils/Utils.hpp"

bool part2 = false;

bool sorter(Range i, Range j) { return (i > j); }

class IngrendientVerifier {
  std::vector<Range> ranges;
  std::vector<long> ingredients;
  std::set<long> freshIngredients;

  enum InputMode {
    Ranges,
    Ingredients
  };

 public:
  IngrendientVerifier(StringVector& input) {
    InputMode iMode = Ranges;
    for (auto line : input) {
      if (line.size() == 0) {
        iMode = Ingredients;
        continue;
      }
      if (iMode == Ranges) {
        StringVector split = Utils::Split(line, "-");
        this->ranges.push_back({stol(split[0]), stol(split[1])});
      } else if (iMode == Ingredients) {
        this->ingredients.push_back(stol(line));
      }
    }
  }

  void FilterRanges() {
    std::vector rangesCopy(this->ranges);
    std::sort(rangesCopy.begin(), rangesCopy.end(), sorter);
    std::vector<Range> filtered;
    for (int i = 0; i < rangesCopy.size(); i++) {
      bool overlapped = false;
      for (const auto range : filtered) {
        if (range.from <= rangesCopy[i].from && range.to >= rangesCopy[i].to) {
          overlapped = true;
        }
      }
      if (!overlapped)
        filtered.push_back(rangesCopy[i]);
    }
    this->ranges = filtered;
  }

  void Verify() {
#if MULTITHREAD
    omp_lock_t writelock;
    omp_init_lock(&writelock);
#pragma omp parallel for
#endif
    for (const auto range : this->ranges) {
      for (const auto ing : this->ingredients) {
        if (ing >= range.from && ing <= range.to) {
#if MULTITHREAD
          omp_set_lock(&writelock);
          this->freshIngredients.insert(ing);
          omp_unset_lock(&writelock);
#else
          this->freshIngredients.insert(ing);
#endif
        }
      }
    }
#if MULTITHREAD
    omp_destroy_lock(&writelock);
#endif
  }

  int GetNumFreshIngredients() {
    return this->freshIngredients.size();
  }

  long CalculateFreshIngredientIDs() {
    long total = 0;
    std::vector<Range> rangesProcessed;
#if MULTITHREAD
    omp_lock_t writelock;
    omp_init_lock(&writelock);
#pragma omp parallel for reduction(+ : total)
#endif
    for (const auto& range : this->ranges) {
      bool noOverlaps = true;
      for (auto& pRange : rangesProcessed) {
        if (range.from >= pRange.from && range.to <= pRange.to) {
          noOverlaps = false;
          continue;
        } else if (range.from < pRange.from && range.to >= pRange.from) {
          total += pRange.from - range.from;
          noOverlaps = false;
          pRange.from = range.from;
        } else if (range.to > pRange.to && range.from <= pRange.to) {
          total += range.to - pRange.to;
          pRange.to = range.to;
          noOverlaps = false;
        }
      }
      if (noOverlaps) {
        total += range.to - range.from + 1;

#if MULTITHREAD
        omp_set_lock(&writelock);
        rangesProcessed.push_back(range);
        omp_unset_lock(&writelock);
#else
        rangesProcessed.push_back(range);
#endif
      }
    }
#if MULTITHREAD
    omp_destroy_lock(&writelock);
#endif
    return total;
  }
};

int main(int argc, char* argv[]) {
  StringVector input = Utils::LoadFile(argc, argv, part2);

  Timer timer = Timer();
  timer.Start();

  IngrendientVerifier iVerifier(input);

  iVerifier.FilterRanges();

  if (!part2) {
    iVerifier.Verify();
    std::cout << "Num fresh ingredients: " << iVerifier.GetNumFreshIngredients() << '\n';
  } else {
    std::cout << "Num fresh IDs: " << iVerifier.CalculateFreshIngredientIDs() << '\n';
  }

  timer.End();

  return 0;
}
