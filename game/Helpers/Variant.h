#pragma once

#include "godot_cpp/variant/typed_array.hpp"

template <typename T>
T getEnumAtIndex(const TypedArray<T>& array, int index) {
  return static_cast<T>(static_cast<int>(array[index]));
}
