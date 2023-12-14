// Measurements.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H
#include <sstream>
#include <type_traits>
#include <string_view>
#include <vector>
#include <tuple>
#include "MeasurementType.h"

namespace DataLogger
{
  template<typename T>
    requires
      std::is_copy_constructible_v<T> &&
      std::is_copy_assignable_v<T> &&
      requires (T x) { x.get_value(); } &&
      requires (T x, T y) { x < y; }

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
    requires
      std::is_copy_constructible_v<T> &&
      std::is_copy_assignable_v<T> &&
      requires (T x) { x.get_value(); } &&
      requires (T x, T y) { x < y; }
  void Measurements<T>::add(value_type value) {
    measures.emplace_back(value);
  }

  template<typename T>
    requires
      std::is_copy_constructible_v<T> &&
      std::is_copy_assignable_v<T> &&
      requires (T x) { x.get_value(); } &&
      requires (T x, T y) { x < y; }
  std::vector<T> Measurements<T>::data() const {
    return measures;
  }

  template<typename T>
    requires
      std::is_copy_constructible_v<T> &&
      std::is_copy_assignable_v<T> &&
      requires (T x) { x.get_value(); } &&
      requires (T x, T y) { x < y; }
  std::tuple<std::string_view, MeasurementType, size_t> Measurements<T>::summary() const
  {
      return {id, type, measures.size()};
  }

}
#endif
