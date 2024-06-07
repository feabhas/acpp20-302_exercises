// alarm.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

module;

#include <iostream>

module Alarms;

namespace Alarms
{
  Alarm::Alarm(Type type, bool status)
  : type{type}, status{status}
  {}

  void Alarm::reset() 
  {
    status = false;
  }

  std::ostream& operator<< (std::ostream& out, const Alarm& alarm)
  {
    out << "Alarm " << int(alarm.type) << ": " << (alarm.status ? "on" : "off");
    return out;
  }
}
