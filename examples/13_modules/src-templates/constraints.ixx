// handler.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd
module;

#include <concepts>

export module Constraints;

export template <typename T>
concept Resetable = requires(T t)
{
  { t.reset() } -> std::same_as<void>;
};
