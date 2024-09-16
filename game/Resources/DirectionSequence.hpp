//
// Created by Zach on 2024-08-17.
//

#pragma once

#include <godot_cpp/classes/resource.hpp>

namespace Game {
  class DirectionSequence final : public godot::Resource {
    GDCLASS(DirectionSequence, Resource)

  private:
    godot::TypedArray<int> sequence;

  public:
    void SetSequence(const godot::TypedArray<int>& sequence) { this->sequence = sequence; }
    [[nodiscard]] godot::TypedArray<int> GetSequence() const { return this->sequence; }

  protected:
    static void _bind_methods();
  };
}
