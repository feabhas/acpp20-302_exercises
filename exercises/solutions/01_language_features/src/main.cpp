// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <array>
#include "Measurement.h"
#include "Measurements.h"

using DataLogger::MeasurementType;
using DataLogger::Measurement;
using DataLogger::Measurements;

int main() {
  std::array<Measurement, 5> measurements {
    Measurement{21.1},   Measurement{18.7},   Measurement{19.6},
    Measurement{22.3},   Measurement{20.1},
  };
  for (auto measure: measurements) {
    std::cout << measure.get_value() << '\n';
  }
  std::cout << '\n';

  Measurements base {"base station", MeasurementType::temperature};
  for (auto m : {21.1, 18.7, 19.6, 22.3, 20.1}) {
    base.add(m);
  }
  for (auto measures = base.data(); auto measure: measures) {
    std::cout << measure.get_value() << '\n';
  }
}
