#ifndef USELESS_DATA_CONTEXT_HPP
#define USELESS_DATA_CONTEXT_HPP

#include <atomic>

struct UselessData {
  std::atomic<int> randomNumber;
  std::atomic<char> randomChar;
  std::atomic<float> randomFloat;
  std::atomic<bool> randomBool;
};

#endif // USELESS_DATA_CONTEXT_HPP
