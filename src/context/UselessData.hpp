#ifndef USELESS_DATA_CONTEXT_HPP
#define USELESS_DATA_CONTEXT_HPP

#include <atomic>

struct UselessData {
  std::atomic<int> random_number;
  std::atomic<char> random_char;
  std::atomic<float> random_float;
  std::atomic<bool> random_bool;
};

#endif // USELESS_DATA_CONTEXT_HPP
