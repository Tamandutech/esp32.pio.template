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

  void getLinePosition();
  void getLineAngle();
  void getPID();

private:
  const int sensor_quantity;
  PathControllerConstants constants;

  float integralSummation;
};

PathController::PathController(PathControllerParamSchema &param)
    : constants(param.constants), sensor_quantity(param.sensor_quantity) {}

void PathController::getLinePosition() {}

void PathController::getLineAngle() {}

void PathController::getPID() {}

#endif // PATH_CONTROLLER_HPP
