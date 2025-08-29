#ifndef PATH_CONTROLLER_HPP
#define PATH_CONTROLLER_HPP

#include <atomic>

#include "context/UselessData.hpp"

struct PathControllerConstants {
  const float kP;
  const float kI;
  const float kD;
};

struct PathControllerParamSchema {
  const int sensor_quantity;
  const PathControllerConstants constants;
};

class PathController {
public:
  PathController(PathControllerParamSchema &param);

  float getLinePosition();
  float getLineAngle();
  float getPID();

private:
  const int sensor_quantity;
  PathControllerConstants constants;

  float integralSummation;
  float lastError;
};

PathController::PathController(PathControllerParamSchema &param)
    : constants(param.constants), sensor_quantity(param.sensor_quantity),
      integralSummation(0.0f), lastError(0.0f) {}

float PathController::getLinePosition() { return 0.0f; }

float PathController::getLineAngle() { return 0.0f; }

float PathController::getPID() {
  float error = getLineAngle();
  integralSummation += error;
  float derivative = error - lastError;
  lastError        = error;
  return constants.kP * error + constants.kI * integralSummation +
         constants.kD * derivative;
}

#endif // PATH_CONTROLLER_HPP
