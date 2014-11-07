#pragma once

#include <chrono>

namespace Graphene {

class TimeWatch {
public:
  TimeWatch() {
    Reset();
  }

  void Reset() {
    start = std::chrono::system_clock::now();
  }

  double Stop() {
    end = std::chrono::system_clock::now();
    return std::chrono::duration<double>(end - start).count();
  }
private:
  std::chrono::time_point<std::chrono::system_clock> start, end;
};

}