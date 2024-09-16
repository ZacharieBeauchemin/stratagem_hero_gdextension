//
// Created by Zach on 2024-08-17.
//

#include "DirectionSequence.hpp"

#include "../Helpers/Binding.hpp"

using namespace godot;

void Game::DirectionSequence::_bind_methods() {
  BIND_PROPERTY(
    Variant::ARRAY,
    "sequence",
    GetSequence,
    SetSequence,
    PROPERTY_HINT_TYPE_STRING,
    String::num(Variant::INT) + "/" + String::num(PROPERTY_HINT_ENUM) + ":Up,Down,Left,Right")
}
