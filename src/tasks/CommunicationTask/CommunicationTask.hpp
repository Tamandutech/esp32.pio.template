#ifndef COMMUNICATION_TASK_HPP
#define COMMUNICATION_TASK_HPP

#include "context/UselessData.hpp"

struct CommunicationTaskParamSchema {
  UselessData &uselessData;
};

void communicationTaskLoop(void *params) {
  CommunicationTaskParamSchema *param = (CommunicationTaskParamSchema *)params;

  for(;;) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

#endif // COMMUNICATION_TASK_HPP
