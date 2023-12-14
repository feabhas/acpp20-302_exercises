// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <cassert>
#include <algorithm>
#include "Measurement.h"
#include "Measurements.h"
#include "Constraints.h"

using DataLogger::MeasurementType;
using DataLogger::Measurement;
using DataLogger::Measurements;
using DataLogger::MeasurementsContainer;

static_assert(requires (Measurements<Measurement> m){
  m.add(typename Measurements<Measurement>::value_type{});
});

template <typename T, typename... P>
MeasurementsContainer auto make_container(P&&... param)
{
  return Measurements<T> { std::forward<P>(param)... };
}

int main() {
  MeasurementsContainer auto base = make_container<Measurement>("base station", MeasurementType::temperature);
  for (auto m : {21.1, 18.7, 19.6, 22.3, 20.1}) {
    base.add(m);
  }

  auto [name, type, size] = base.summary();
  std::cout << name << "(" << to_string(type) << ") "
      << size << " values" << '\n';
}
