// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <cassert>
#include <ranges>
#include <algorithm>
#include <span>
#include "Measurement.h"
#include "Measurements.h"
#include "Constraints.h"

using DataLogger::MeasurementType;
using DataLogger::Measurement;
using DataLogger::Measurements;
using DataLogger::MeasurementsContainer;
namespace ranges = std::ranges;
namespace views = std::views;

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

  auto [min, max] = base.min_max();
  std::cout << "Min " << min.get_value() << ", max " << max.get_value() << '\n';

  auto measures = base.data();
  ranges::sort(measures);
  ranges::for_each(measures, [](auto m){std::cout << m.get_value() << ' ';});
  std::cout << '\n';

  auto average = (min.get_value() + max.get_value()) / 2.0;
  std::cout << "Average " << average << '\n';

  measures = base.data();
  for (auto m : measures
       | views::transform([] (auto m) { return m.get_value(); })
       | views::filter([average] (auto value) { return value < average; })
     ) {
      std::cout << m << ' ';
  }
  std::cout << '\n';

  for (auto m : base
      | views::transform([] (auto m) { return m.get_value(); })
      | views::filter([average] (auto value) { return value < average; })
    ) {
    std::cout << m << ' ';
  }
  std::cout << '\n';
}
