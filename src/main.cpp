// Framework
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/timers.h"

// Context
#include "context/RobotEnv.hpp"
#include "context/UselessData.hpp"
// Non-volatile storage
#include "storage/storage.hpp"
// Tasks
#include "tasks/CommunicationTask/CommunicationTask.hpp"
#include "tasks/MainTask/MainTask.hpp"

UselessData uselessData;

extern "C" {
void app_main(void);
}

void app_main() {
  uselessData.random_number.store(10, std::memory_order_relaxed);
  uselessData.random_char.store('b', std::memory_order_relaxed);
  uselessData.random_float.store(20.0f, std::memory_order_relaxed);
  uselessData.random_bool.store(true, std::memory_order_relaxed);

  Storage::write(uselessData.random_number.load(std::memory_order_relaxed));
  Storage::write(uselessData.random_char.load(std::memory_order_relaxed));
  Storage::write(uselessData.random_float.load(std::memory_order_relaxed));
  Storage::write(uselessData.random_bool.load(std::memory_order_relaxed));

  MainTaskParamSchema mainTaskParam                   = {uselessData};
  CommunicationTaskParamSchema communicationTaskParam = {uselessData};

  // Task
  // 1 word = 4 bytes
  // The stack depth is setup to 60000 words, which is 240KB.
  TaskHandle_t mainTaskHandle;
  xTaskCreatePinnedToCore(mainTaskLoop, "MainTask", 60000, &mainTaskParam, 1,
                          &mainTaskHandle, 0); // Run on Core 0


  TaskHandle_t communicationTaskHandle;
  xTaskCreatePinnedToCore(communicationTaskLoop, "CommunicationTask", 60000,
                          &communicationTaskParam, 1, &communicationTaskHandle,
                          1); // Run on Core 1

  for(;;) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
