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
    static constexpr double eps {1e-3};

    Measurement() = default;
    explicit Measurement(double value) : value{value} {}
    double get_value() const { return value; }

  private:
    double value {};
  };
}
#endif
