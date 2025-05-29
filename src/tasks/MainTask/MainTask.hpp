#ifndef MAIN_TASK_HPP
#define MAIN_TASK_HPP

#include "context/UselessData.hpp"

#include "drivers/MotorDriver/MotorDriver.hpp"

#include "tasks/MainTask/SpeedControl/SpeedControl.hpp"

class MainTask {
public:
  MainTask(UselessData &data);

  void loop();

private:
  UselessData &data;
  MotorDriver *motorDriver;
  SpeedControl *speedControl;
};

MainTask::MainTask(UselessData &data) : data(data) {
  motorDriver  = new MotorDriver(data);
  speedControl = new SpeedControl(data);
}

void MainTask::loop() {}

#endif // MAIN_TASK_HPP
