// Measurement.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef MEASUREMENT_H
#define MEASUREMENT_H
#include <cmath>

namespace DataLogger
{
  class Measurement
  {
  public:
    using value_type = double;
    static constexpr value_type eps {1e-3};

    Measurement() = default;
    explicit Measurement(value_type value) : value{value} {}
    value_type get_value() const { return value; }

  private:
    value_type value {};
  };
}
#endif
