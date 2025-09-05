#ifndef MOTOR_DRIVER_HPP
#define MOTOR_DRIVER_HPP

#include "context/UselessData.hpp"

class MotorDriver {
public:
  MotorDriver(UselessData &data);

  void pwmOutput(int32_t value);
  int32_t getPulse();

private:
  UselessData &data_;
};

MotorDriver::MotorDriver(UselessData &data) : data_(data) {}

void MotorDriver::pwmOutput(int32_t value) {}

int32_t MotorDriver::getPulse() { return 0; }

#endif // MOTOR_DRIVER_HPP
