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
  const int sensorQuantity;
  const PathControllerConstants constants;
};

class PathController {
public:
  PathController(PathControllerParamSchema &param);

  float getLinePosition();
  float getLineAngle();
  float getPID();

private:
  const int sensorQuantity_;
  PathControllerConstants constants_;

  float integralSummation_;
  float lastError_;
};

PathController::PathController(PathControllerParamSchema &param)
    : constants_(param.constants), sensorQuantity_(param.sensorQuantity),
      integralSummation_(0.0F), lastError_(0.0F) {}

float PathController::getLinePosition() { return 0.0F; }

float PathController::getLineAngle() { return 0.0F; }

float PathController::getPID() {
  float error = getLineAngle();
  integralSummation_ += error;
  float derivative = error - lastError_;
  lastError_       = error;
  return constants_.kP * error + constants_.kI * integralSummation_ +
         constants_.kD * derivative;
}

#endif // PATH_CONTROLLER_HPP
