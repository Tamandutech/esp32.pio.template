#ifndef COMMUNICATION_TASK_HPP
#define COMMUNICATION_TASK_HPP

#include "context/UselessData.hpp"

class CommunicationTask {
public:
  CommunicationTask(UselessData &data);

  void loop();

private:
  UselessData &data;
};

CommunicationTask::CommunicationTask(UselessData &data) : data(data) {}

void CommunicationTask::loop() {}

#endif // COMMUNICATION_TASK_HPP
