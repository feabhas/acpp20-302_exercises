// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <string_view>
#include "Constraints.h"
import Measurements;

using DataLogger::MeasurementType;
using DataLogger::Measurement;
using DataLogger::Measurements;
using DataLogger::MeasurementsContainer;

int main() {
  Measurements<Measurement> base {"base station", MeasurementType::temperature};
  // for (auto m : {21.1, 18.7, 19.6, 22.3, 20.1}) {
  //   base.add(m);
  // }

  // for (auto measurements = base.data(); auto& m: measurements) {
  //   std::cout << m.get_value() << ' ';
  // }
  // std::cout << '\n';
}

