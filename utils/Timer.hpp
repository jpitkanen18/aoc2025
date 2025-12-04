#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

class Timer {
  std::chrono::steady_clock::time_point t_start;
  bool IsRunning = false;

 public:
  Timer() {}

  void Start() {
    t_start = std::chrono::high_resolution_clock::now();
    IsRunning = true;
  }

  void End() {
    if (!IsRunning) {
      std::cout << "Did you forget to start the timer?" << '\n';
      IsRunning = false;
      return;
    }
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    long minutes = elapsed_time_ms / 1000 / 60;
    long seconds = (elapsed_time_ms - (minutes * 1000 * 60)) / 1000;
    std::cout << "Elapsed time: " << minutes << " minutes, " << seconds << " seconds" << std::endl;
    std::cout << "Elapsed time ms: " << elapsed_time_ms << '\n';
    IsRunning = false;
  }
};
