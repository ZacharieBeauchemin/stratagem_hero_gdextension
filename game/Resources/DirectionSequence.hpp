//
// Created by Zach on 2024-08-17.
//

#pragma once

#include <godot_cpp/classes/resource.hpp>

#include "Direction.hpp"

namespace Game {
  class DirectionSequence final : public godot::Resource {
    GDCLASS(DirectionSequence, Resource)

  private:
    godot::TypedArray<Direction> sequence;

  public:
    void SetSequence(const godot::TypedArray<Direction>& sequence) { this->sequence = sequence; }
    [[nodiscard]] godot::TypedArray<Direction> GetSequence() const { return this->sequence; }

  protected:
    static void _bind_methods();
  };
}
