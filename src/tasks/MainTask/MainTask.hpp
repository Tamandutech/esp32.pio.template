#ifndef MAIN_TASK_HPP
#define MAIN_TASK_HPP

#include "context/UselessData.hpp"

class MainTask {
public:
  MainTask(UselessData &data);

  void loop();

private:
  UselessData &data;
};

MainTask::MainTask(UselessData &data) : data(data) {}

void MainTask::loop() {}

#endif // MAIN_TASK_HPP
