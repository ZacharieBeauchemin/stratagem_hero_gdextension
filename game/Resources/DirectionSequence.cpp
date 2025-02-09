#include "DirectionSequence.hpp"

#include "../Helpers/BindProperty.hpp"

using namespace godot;

void Game::DirectionSequence::_bind_methods() {
  BIND_ARRAY_PROPERTY(
    "sequence",
    &DirectionSequence::GetSequence,
    &DirectionSequence::SetSequence,
    String::num(Variant::INT) + "/" + String::num(PROPERTY_HINT_ENUM) + ":Up,Down,Left,Right")
}
