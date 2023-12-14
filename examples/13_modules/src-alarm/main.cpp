// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
import Handler;

using Alarms::Alarm;

int main()
{
  Alarm a1 {Alarm::Type::critical, true};
  Handler::cancel(a1);
  std::cout << a1 << '\n';
}

