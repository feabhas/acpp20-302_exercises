// handler.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

module Handler;

namespace Handler {
  void cancel (Alarms::Alarm& alarm) {
    alarm.reset();
  }
};
