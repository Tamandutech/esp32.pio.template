#ifndef SPEED_CONTROL_HPP
#define SPEED_CONTROL_HPP

#include "context/UselessData.hpp"


class SpeedControl {
public:
  SpeedControl(UselessData &data);

  void get();

private:
  UselessData &data;
};

SpeedControl::SpeedControl(UselessData &data) : data(data) {}

void SpeedControl::get() {}

#endif // SPEED_CONTROL_HPP
