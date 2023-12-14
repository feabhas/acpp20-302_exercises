// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <cassert>
#include <algorithm>
#include "Measurement.h"
#include "Measurements.h"

using DataLogger::MeasurementType;
using DataLogger::Measurement;
using DataLogger::Measurements;

int main() {
  Measurements base {"base station", MeasurementType::temperature};
  for (auto m : {21.1, 18.7, 19.6, 22.3, 20.1}) {
    base.add(m);
  }

  Measurements::add_type measure{17.9};
  assert(base.add(measure));
  measure = "22.1";
  assert(base.add(measure));
  measure = "warm";
  assert(! base.add(measure));

  auto [name, type, size] = base.summary();
  std::cout << name << "(" << to_string(type) << ") "
            << size << " values" << '\n';
}
