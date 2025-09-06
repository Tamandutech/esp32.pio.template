#ifndef COMMUNICATION_TASK_HPP
#define COMMUNICATION_TASK_HPP

#include "context/GlobalData.hpp"

struct CommunicationTaskParamSchema {
  GlobalData &globalData;
};

void communicationTaskLoop(void *params) {
  CommunicationTaskParamSchema *param =
      static_cast<CommunicationTaskParamSchema *>(params);
  (void)param; // Suppress unused variable warning

  for(;;) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

#endif // COMMUNICATION_TASK_HPP
