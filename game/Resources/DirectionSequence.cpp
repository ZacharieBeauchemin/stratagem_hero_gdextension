//
// Created by Zach on 2024-08-17.
//

#include "DirectionSequence.hpp"

using namespace godot;

void Game::DirectionSequence::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_sequence", "sequence"), &DirectionSequence::SetSequence);
  ClassDB::bind_method(D_METHOD("get_sequence"), &DirectionSequence::GetSequence);

  ADD_PROPERTY(
    PropertyInfo(
      Variant::ARRAY,
      "sequence",
      PROPERTY_HINT_TYPE_STRING,
      String::num(Variant::INT) + "/" + String::num(PROPERTY_HINT_ENUM) + ":Up,Down,Left,Right"),
    "set_sequence",
    "get_sequence");
}
