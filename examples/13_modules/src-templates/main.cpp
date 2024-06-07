// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
import Alarms;
import Templates;

using Alarms::Alarm;

int main()
{
  Alarm a1 {Alarm::Type::critical, true};
  do_reset(a1);
  std::cout << a1 << '\n';
}

