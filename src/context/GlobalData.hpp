#ifndef GLOBAL_DATA_CONTEXT_HPP
#define GLOBAL_DATA_CONTEXT_HPP

#include <atomic>

struct GlobalData {
  std::atomic<int> randomNumber;
  std::atomic<char> randomChar;
  std::atomic<float> randomFloat;
  std::atomic<bool> randomBool;
};

#endif // GLOBAL_DATA_CONTEXT_HPP
