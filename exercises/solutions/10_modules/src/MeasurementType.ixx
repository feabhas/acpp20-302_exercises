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
#include <cstddef>
// #include <string_view>
#include <array>
export module MeasurementType;

export namespace DataLogger 
{
  enum class MeasurementType {unknown, temperature, pressure, minT, maxT};

  // gcc 13.1 fails to compile if return type is std::string_view
  constexpr const char* to_string(MeasurementType type) {
    constexpr std::array names {
      "unknown", "temperature", "pressure", "minT", "maxT"
    };
    return names[size_t(type)];
  }
}
