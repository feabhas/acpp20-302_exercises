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
// #include <sstream>
#include <string_view>
#include <vector>
#include <tuple>
#include <algorithm>
#include "Constraints.h"
#include "Generator.h"

export module Measurements;
export import Measurement;

export namespace DataLogger 
{
  template<Measurable T>
  class Measurements
  {
  public:
    using value_type = T::value_type;
    using measurement_type = T;

    Measurements(std::string_view id, MeasurementType type)
    : id{id}, type{type}
    {
      measures.reserve(10);
    }

    void add(value_type value);

    std::vector<T> data() const;
	  std::tuple<std::string_view, MeasurementType, size_t> summary() const;
	
    std::string to_string() const;

    size_t size() const {
      return measures.size();
    }             

    auto min_max() {
      return std::ranges::minmax(measures);
    }

    Generator<Measurement> values(double min, double max);

    // using iterator = std::vector<T>::iterator;
    // iterator begin() { return measures.begin(); }
    // iterator end() { return measures.end(); }

  private:
    std::string_view id {};
    MeasurementType type {};
    std::vector<T> measures {};
  };

  template<Measurable T>
  void Measurements<T>::add(value_type value) {
    measures.emplace_back(value);
  }

  template<Measurable T>
  std::vector<T> Measurements<T>::data() const {
    return measures;
  }

  template<Measurable T>
  std::tuple<std::string_view, MeasurementType, size_t> Measurements<T>::summary() const
  {
      return {id, type, measures.size()};
  }

  template<Measurable T>
  Generator<Measurement> Measurements<T>::values(double min, double max)
  {
    for (auto measure : measures) {
      if (min <= measure.get_value() && measure.get_value() <= max) {
        co_yield measure;
      }
    }
  }
}
