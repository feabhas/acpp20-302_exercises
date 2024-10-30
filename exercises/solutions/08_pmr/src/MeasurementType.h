// MeasurementType.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef MEASUREMENT_TYPE_H
#define MEASUREMENT_TYPE_H
#include <cstdint>

#include <string_view>
#include <array>

namespace DataLogger
{
  enum class MeasurementType {unknown, temperature, pressure, minT, maxT};

  constexpr const char* to_string(MeasurementType type) {
    constexpr std::array names {
      "unknown", "temperature", "pressure", "minT", "maxT"
    };
    return names[size_t(type)];
  }
}
#endif
