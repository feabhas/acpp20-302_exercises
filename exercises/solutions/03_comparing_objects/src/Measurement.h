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
    // Measurement(const Measurement&&) = delete;
    double get_value() const { return value; }

    std::partial_ordering operator<=>(const Measurement& rhs) const
    {
      auto diff = fabs(value - rhs.value);
      if (diff <= eps)            return std::partial_ordering::equivalent;
      else if (value < rhs.value) return std::partial_ordering::less;
      else if (value > rhs.value) return std::partial_ordering::greater;
      return std::partial_ordering::unordered;
    }

    bool operator==(const Measurement& rhs) const
    {
      return (*this <=> rhs) == std::partial_ordering::equivalent;
    }

  private:
    double value {};
  };
}
#endif
