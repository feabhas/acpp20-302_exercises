// alarm-extra.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

module Alarm;
import :Helper;

namespace Alarms
{
  const char* to_string(Alarms::Alarm::Type type) {
    return type_names[int(type)];
  }
}
