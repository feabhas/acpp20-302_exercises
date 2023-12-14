// Measurements.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H
#include <sstream>
#include <string_view>
#include <vector>
#include <tuple>
#include <algorithm>
#include "MeasurementType.h"
#include "Constraints.h"
#include "Generator.h"

namespace DataLogger
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

    size_t size() const {
      return measures.size();
    }

    auto min_max() {
      return std::ranges::minmax(measures);
    }

    Generator<Measurement> values(double min, double max);

    using iterator = std::vector<T>::iterator;

    iterator begin() { return measures.begin(); }
    iterator end() { return measures.end(); }

  private:
    std::string id {};
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
#endif
