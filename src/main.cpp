// Context
#include "context/RobotEnv.hpp"
#include "context/UselessData.hpp"
// Non-volatile storage
#include "storage/storage.hpp"
// Tasks
#include "tasks/CommunicationTask/CommunicationTask.hpp"
#include "tasks/MainTask/MainTask.hpp"

MainTask *mainTask;
CommunicationTask *communicationTask;
UselessData uselessData;

void setup() {
  uselessData.random_number.store(10, std::memory_order_relaxed);
  uselessData.random_char.store('b', std::memory_order_relaxed);
  uselessData.random_float.store(20.0f, std::memory_order_relaxed);
  uselessData.random_bool.store(true, std::memory_order_relaxed);

  Storage::write(uselessData.random_number.load(std::memory_order_relaxed));
  Storage::write(uselessData.random_char.load(std::memory_order_relaxed));
  Storage::write(uselessData.random_float.load(std::memory_order_relaxed));
  Storage::write(uselessData.random_bool.load(std::memory_order_relaxed));

  communicationTask = new CommunicationTask(uselessData);
  communicationTask->loop();

  mainTask = new MainTask(uselessData);
  mainTask->loop();
}
