#ifndef MAIN_TASK_HPP
#define MAIN_TASK_HPP

#include "context/UselessData.hpp"

#include "drivers/MotorDriver/MotorDriver.hpp"

#include "tasks/MainTask/PathController/PathController.hpp"

struct MainTaskParamSchema {
  UselessData &uselessData;
};

void mainTaskLoop(void *params) {
  MainTaskParamSchema *param = static_cast<MainTaskParamSchema *>(params);
  MotorDriver *motorDriver   = new MotorDriver(param->uselessData);
  (void)motorDriver; // Suppress unused variable warning

  PathControllerParamSchema pathControllerParam = {
      .sensorQuantity = 4,
      .constants      = {.kP = 0.1, .kI = 0.01, .kD = 0.001},
  };
  PathController *pathController = new PathController(pathControllerParam);
  (void)pathController; // Suppress unused variable warning

  for(;;) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

#endif // MAIN_TASK_HPP
