// Context
#include "context/UselessData.hpp"
// Non-volatile storage
#include "storage/storage.hpp"
// Tasks
#include "tasks/MyTask.hpp"

MyTask *myTask;

void setup() {
  UselessData::random_number = 10;
  UselessData::random_char   = 'b';
  UselessData::random_float  = 20.0f;
  UselessData::random_bool   = true;

  myTask = new MyTask(UselessData::random_number);
  myTask->loop();

  Storage::write(UselessData::random_number);
  Storage::write(UselessData::random_char);
  Storage::write(UselessData::random_float);
  Storage::write(UselessData::random_bool);
}

void loop() {}