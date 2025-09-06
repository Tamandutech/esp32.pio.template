#ifndef MOTOR_DRIVER_HPP
#define MOTOR_DRIVER_HPP

#include "context/GlobalData.hpp"

class MotorDriver {
public:
  MotorDriver(GlobalData &data);

  void    pwmOutput(int32_t value);
  int32_t getPulse();

private:
  GlobalData &data_;
};

MotorDriver::MotorDriver(GlobalData &data) : data_(data) {}

void MotorDriver::pwmOutput(int32_t value) {}

int32_t MotorDriver::getPulse() { return 0; }

#endif // MOTOR_DRIVER_HPP
