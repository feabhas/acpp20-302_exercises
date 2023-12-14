// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <span>
#include <algorithm>
#include "Measurement.h"
#include "Measurements.h"
#include "Generator.h"

using DataLogger::MeasurementType;
using DataLogger::Measurement;
using DataLogger::Measurements;

Generator<double> generate_data(int count, double start=20.0, double variance=2.0)
{
  double value = start;
  for (int i=0; i<count; ++i) {
    value += (rand()%20 - 10) * variance / 10.0;
    co_yield value;
  }
}

int main()
{
  Measurements<Measurement> base {"base station", MeasurementType::temperature};
  for (auto value : generate_data(20)) {
    base.add(value);
  }

  auto [name, type, size] = base.summary();
  std::cout << name << "(" << to_string(type) << ") "
            << size << " values" << '\n';

  for (auto value : base.values(18.0, 22.0)) {
    std::cout << value.get_value() << ' ';
  }
  std::cout << '\n';
}
