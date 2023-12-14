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
#include "MeasurementType.h"

namespace DataLogger
{
  template<typename T>
  class Measurements
  {
  public:
    using value_type = T::value_type;

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

  private:
    std::string id {};
    MeasurementType type {};
    std::vector<T> measures {};
  };

  template<typename T>
  void Measurements<T>::add(value_type value) {
    measures.emplace_back(value);
  }

  template<typename T>
  std::vector<T> Measurements<T>::data() const {
    return measures;
  }

  template<typename T>
  std::tuple<std::string_view, MeasurementType, size_t> Measurements<T>::summary() const
  {
      return {id, type, measures.size()};
  }

}
#endif
