// Constraints.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H
#include <concepts>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include "MeasurementType.h"

namespace DataLogger
{
  template<typename T>
  concept Measurable = requires {
    requires std::semiregular<T> &&
    requires (T x) { x.get_value(); } &&
    requires (T x, T y) { x < y; };
  };


  template <typename T>
  concept MeasurementsContainer = requires(T t) {
    { t.add(typename T::value_type{}) };
    { t.size() } -> std::same_as<size_t>;
    { t.data() } -> std::same_as<std::vector<typename T::measurement_type>>;
    { t.summary() } -> std::same_as<std::tuple<std::string, MeasurementType, size_t>>;
  };
}

#endif
