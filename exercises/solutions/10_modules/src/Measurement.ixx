// -----------------------------------------------------------------------------
// DISCLAIMER:
// Feabhas is furnishing this item "as is". Feabhas does not provide any
// warranty of the item whatsoever, whether express, implied, or statutory,
// including, but not limited to, any warranty of merchantability or fitness
// for a particular purpose or any warranty that the contents of the item will
// be error-free.
// In no respect shall Feabhas incur any liability for any damages, including,
// but limited to, direct, indirect, special, or consequential damages arising
// out of, resulting from, or any way connected to the use of the item, whether
// or not based upon warranty, contract, tort, or otherwise; whether or not
// injury was sustained by persons or property or otherwise; and whether or not
// loss was sustained from, or arose out of, the results of, the item, or any
// services that may be provided by Feabhas.
// -----------------------------------------------------------------------------
module;
#include <cmath>

export module Measurement;

export import MeasurementType;

export namespace DataLogger 
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
