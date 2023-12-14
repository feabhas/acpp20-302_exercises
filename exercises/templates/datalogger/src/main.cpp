// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <array>
#include "Measurement.h"
#include "MeasurementType.h"

using DataLogger::MeasurementType;
using DataLogger::Measurement;

int main() {
  std::array<Measurement, 5> measurements {
    Measurement{21.1},   Measurement{18.7},   Measurement{19.6},
    Measurement{22.3},   Measurement{20.1},
  };
  std::cout << measurements.size() << '\n';
}
