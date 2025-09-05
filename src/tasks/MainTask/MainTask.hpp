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

  // Array de valores dos sensores (placeholder - deve ser inicializado com
  // dados reais)
  int sensorValues[12] = {0}; // Inicializa com zeros

  PathControllerParamSchema pathControllerParam = {
      .constants      = {.kP = 0.1F, .kI = 0.01F, .kD = 0.001F},
      .sensorQuantity = 12,
      .sensorValues   = &sensorValues[0],
      .maxAngle       = 45.0F, // Ângulo máximo de 45 graus
      .radiusSensor   = 100, // Raio dos sensores em mm
      .sensorToCenter = 50, // Distância do sensor ao centro em mm
  };
  PathController *pathController = new PathController(pathControllerParam);

  for(;;) {
    float pathPID = pathController->getPID();

    // TODO: Use motorDriver to apply PID output to motors
    // motorDriver->setSpeed(pathPID);

    // Suppress unused variable warnings - these will be used for motor control
    (void)motorDriver;
    (void)pathPID;

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

#endif // MAIN_TASK_HPP
