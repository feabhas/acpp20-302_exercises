// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
import Alarm;
using Alarms::Alarm;

int main()
{
  Alarm a1 {Alarm::Type::critical, true};
  std::cout << a1 << '\n';
  std::cout << Alarms::to_string(a1.get_type()) << '\n';
}

