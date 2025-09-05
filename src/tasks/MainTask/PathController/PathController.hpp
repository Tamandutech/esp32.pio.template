#ifndef PATH_CONTROLLER_HPP
#define PATH_CONTROLLER_HPP

#include <atomic>
#include <cmath>

#include "context/UselessData.hpp"

/**
 * @brief Estrutura que contém as constantes do controlador PID
 *
 * Define os parâmetros de ganho para o controlador
 * proporcional-integral-derivativo usado no controle de direção do robô.
 */
struct PathControllerConstants {
  const float kP; // Ganho proporcional do PID
  const float kI; // Ganho integral do PID
  const float kD; // Ganho derivativo do PID
};

/**
 * @brief Estrutura que define os parâmetros de inicialização do PathController
 *
 * Contém todas as configurações necessárias para inicializar o controlador de
 * caminho, incluindo constantes PID, quantidade de sensores e valores dos
 * sensores.
 */
struct PathControllerParamSchema {
  const PathControllerConstants constants; // Constantes do controlador PID
  const int sensorQuantity;                // Quantidade de sensores de linha
  const int *sensorValues;       // Ponteiro para array de valores dos sensores
  const float maxAngle;          // Ângulo máximo em graus
  const uint16_t radiusSensor;   // Raio dos sensores
  const uint16_t sensorToCenter; // Distância do sensor ao centro
};

/**
 * @brief Classe que implementa o controlador de caminho do robô
 *
 * Esta classe é responsável por processar os dados dos sensores de linha,
 * calcular a posição relativa do robô em relação à linha e fornecer
 * comandos de correção usando um controlador PID.
 */
class PathController {
public:
  PathController(PathControllerParamSchema &param);

  float getLinePosition();

  float getLineAngle();

  float getPID();

private:
  const size_t sensorQuantity_; // Quantidade de sensores de linha
  const int *sensorValues_;     // Ponteiro para array de valores dos sensores
  PathControllerConstants constants_; // Constantes do controlador PID

  // Parâmetros geométricos para cálculo do ângulo
  const float maxAngle_;          // Ângulo máximo em radianos
  const uint16_t radiusSensor_;   // Raio dos sensores
  const uint16_t sensorToCenter_; // Distância do sensor ao centro

  float integralSummation_;       // Acumulador do termo integral do PID
  float lastError_; // Último erro calculado para o termo derivativo

  // Rastreamento do estado dos sensores
  uint32_t lastPosition_; // Última posição calculada da linha
  bool onLine_;           // Indica se o robô está sobre a linha
};

/**
 * @brief Construtor do PathController
 *
 * Inicializa o controlador de caminho com os parâmetros fornecidos,
 * configurando as constantes PID e inicializando as variáveis de estado.
 *
 * @param param Parâmetros de inicialização do controlador
 */
PathController::PathController(PathControllerParamSchema &param)
    : constants_(param.constants), sensorQuantity_(param.sensorQuantity),
      sensorValues_(param.sensorValues),
      maxAngle_(param.maxAngle * M_PI / 180.0F), // Converte graus para radianos
      radiusSensor_(param.radiusSensor), sensorToCenter_(param.sensorToCenter),
      integralSummation_(0.0F), lastError_(0.0F), lastPosition_(0),
      onLine_(false) {}

/**
 * @brief Calcula a posição da linha em relação aos sensores
 *
 * Este método implementa o algoritmo de detecção de posição da linha baseado
 * no método QTRwithMUX::read_all(). Processa os valores dos sensores para
 * determinar a posição relativa do robô em relação à linha.
 *
 * @return Posição da linha (0 a (sensor_quantity-1)*1000), onde o centro é
 * (sensor_quantity-1)*500
 */
float PathController::getLinePosition() {
  // Baseado no método QTRwithMUX::read_all()

  bool onLine =
      false; // se falso até o final, os sensores estão todos fora da linha
  uint32_t avg = 0; // soma ponderada das leituras
  uint32_t sum = 0; // soma das leituras

  // Lê os valores dos sensores do array sensorValues_
  for(size_t i = 0; i < sensorQuantity_; i++) {
    // Lê o valor real do sensor do array
    int sensorValue = sensorValues_[i];

    // Aplica a mesma lógica do QTRwithMUX::read_all()
    if(sensorValue > 200) {
      onLine = true;       // verifica se tem um sensor na linha
    }
    if(sensorValue > 50) { // valores menores que 50 são considerados ruídos
      avg += static_cast<uint32_t>(sensorValue) *
             (i * 1000);   // soma ponderada de cada leitura
      sum += sensorValue;  // soma total das leituras
    }
  }

  if(!onLine) {
    // Se o robô está fora da linha, retorna a direção da última leitura
    // Se a última posição foi à direita do centro, retorna 0
    if(lastPosition_ < (sensorQuantity_ - 1) * 1000 / 2) {
      return 0.0F;
    }
    // Se a última posição foi à esquerda do centro, retorna o valor máximo
    else {
      return static_cast<float>((sensorQuantity_ - 1) * 1000);
    }
  } else {
    // Dividindo avg por sum, obtém-se a posição relativa do robô na linha
    // Com 16 sensores, o centro se encontra no valor 7.500
    lastPosition_ = (avg / sum);
    onLine_       = true;

    // Retorna posição não normalizada (0 a (sensorQuantity_-1)*1000)
    return static_cast<float>(lastPosition_);
  }
}

/**
 * @brief Calcula o ângulo de desvio da linha
 *
 * Calcula o ângulo de desvio do robô em relação à linha baseado na posição
 * atual da linha. Este método converte a posição da linha em um ângulo
 * para correção de direção usando geometria circular.
 *
 * @return Ângulo de desvio em graus (-90° a 90°)
 */
float PathController::getLineAngle() {
  // Obtém a posição atual da linha usando o método getLinePosition
  // Agora retorna valor não normalizado (0 a (sensorQuantity_-1)*1000)
  int32_t position = static_cast<int32_t>(getLinePosition());

  // Subtrai a metade do valor máximo para centralizar a posição em 0
  // Para 16 sensores: vai de 0 a 15000, após subtração vai de -7500 a +7500
  position = position - ((sensorQuantity_ - 1) * 500);

  // Converte a posição para ângulo usando regra de três
  // position vai de -(sensorQuantity_-1)*500 a +(sensorQuantity_-1)*500
  // maxAngle_ vai de -maxAngle_ a +maxAngle_
  float angleRadius = (position * maxAngle_) / ((sensorQuantity_ - 1) * 500);

  // Calcula o ângulo com o centro usando geometria circular
  // Fórmula: atan(sin(angleRadius) / (cos(angleRadius) - 1 +
  // (sensorToCenter_/radiusSensor_)))
  float denominator = cosf(angleRadius) - 1.0F +
                      (static_cast<float>(sensorToCenter_) / radiusSensor_);

  // Evita divisão por zero
  if(fabsf(denominator) < RobotEnv::EPSILON_TOLERANCE) {
    return 0.0F;
  }

  float angleWithCenter = atanf(sinf(angleRadius) / denominator);

  // Converte o ângulo de radianos para graus e retorna
  return angleWithCenter * 180.0F / M_PI;
}

/**
 * @brief Calcula o valor de correção PID
 *
 * Implementa um controlador PID (Proporcional-Integral-Derivativo) para
 * calcular a correção necessária nos motores baseada no erro de posição.
 * O erro é calculado como o ângulo de desvio da linha.
 *
 * @return Valor de correção para os motores (normalizado)
 */
float PathController::getPID() {
  float error = getLineAngle();
  integralSummation_ += error;
  float derivative = error - lastError_;
  lastError_       = error;
  return constants_.kP * error + constants_.kI * integralSummation_ +
         constants_.kD * derivative;
}

#endif // PATH_CONTROLLER_HPP
