// Framework
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/timers.h"

// Context
#include "context/GlobalData.hpp"
#include "context/RobotEnv.hpp"
// Non-volatile storage
#include "storage/storage.hpp"
// Tasks
#include "tasks/CommunicationTask/CommunicationTask.hpp"
#include "tasks/MainTask/MainTask.hpp"

GlobalData globalData;

extern "C" {
void app_main(void);
}

void app_main() {
  globalData.randomNumber.store(10, std::memory_order_relaxed);
  globalData.randomChar.store('b', std::memory_order_relaxed);
  globalData.randomFloat.store(20.0F, std::memory_order_relaxed);
  globalData.randomBool.store(true, std::memory_order_relaxed);

  Storage::write(globalData.randomNumber.load(std::memory_order_relaxed));
  Storage::write(globalData.randomChar.load(std::memory_order_relaxed));
  Storage::write(globalData.randomFloat.load(std::memory_order_relaxed));
  Storage::write(globalData.randomBool.load(std::memory_order_relaxed));

  MainTaskParamSchema          mainTaskParam          = {globalData};
  CommunicationTaskParamSchema communicationTaskParam = {globalData};

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
