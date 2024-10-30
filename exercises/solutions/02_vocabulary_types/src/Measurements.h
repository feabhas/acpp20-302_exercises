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
#include <variant>
#include "MeasurementType.h"

namespace DataLogger
{
  class Measurements
  {
  public:
    using value_type = Measurement::value_type;
    using add_type = std::variant<double, std::string>;

    Measurements(std::string_view id, MeasurementType type)
    : id{id}, type{type}
    {
      measures.reserve(10);
    }

    inline void add(value_type value);
    inline bool add(add_type value);

    inline std::vector<Measurement> data() const;
	inline std::tuple<std::string, MeasurementType, size_t> summary() const;

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

  bool Measurements::add(add_type value)
  {
    if (auto* dp = std::get_if<double>(&value); dp != nullptr) {
        add(*dp);
        return true;
    }
    else if(auto* sv = std::get_if<std::string>(&value); sv != nullptr) {
      char* end {};
      if (double d = std::strtod( sv->data(), &end ); end != sv->data()) {
        add(d);
        return true;
      }
    }
    return false;
  }

  std::vector<Measurement> Measurements::data() const {
    return measures;
  }

  std::tuple<std::string, MeasurementType, size_t> Measurements::summary() const
  {
      return {id, type, measures.size()};
  }

}
#endif
