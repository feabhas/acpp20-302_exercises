// Measurements.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H
#include <string_view>
#include <vector>
#include "MeasurementType.h"

namespace DataLogger
{
  class Measurements
  {
  public:
    using value_type = Measurement::value_type;

    Measurements(std::string_view id, MeasurementType type)
    : id{id}, type{type}
    {
      measures.reserve(10);
    }

    inline void add(value_type value);
    inline std::vector<Measurement> data() const;

    size_t size() const {
      return measures.size();
    }

  private:
    std::string id {};
    MeasurementType type {};
    std::vector<Measurement> measures {};
  };

  void Measurements::add(value_type value) {
    measures.emplace_back(value);
  }

  std::vector<Measurement> Measurements::data() const {
    return measures;
  }

}
#endif
