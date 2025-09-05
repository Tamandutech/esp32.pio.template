#ifndef ROBOT_ENV_HPP
#define ROBOT_ENV_HPP

namespace RobotEnv {

const float ROBOT_WIDTH         = 4;
const float WHEEL_RADIUS        = 4;
const float WHEEL_CIRCUMFERENCE = 4;

const float MAX_SPEED          = 4;
const float MAX_DECELERATION   = 4;
const float MAX_ROTATION_SPEED = 4;

constexpr float EPSILON_TOLERANCE =
    1e-6F; // Tolerância para comparações de ponto flutuante

// Constantes para prevenção de integral windup no PID
constexpr float INTEGRAL_MAX = 1000.0F;  // Valor máximo para o termo integral
constexpr float INTEGRAL_MIN = -1000.0F; // Valor mínimo para o termo integral

} // namespace RobotEnv

#endif // ROBOT_ENV_HPP
