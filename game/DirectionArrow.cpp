//
// Created by Zach on 2024-08-17.
//

#include <godot_cpp/classes/shader_material.hpp>

#include "DirectionArrow.hpp"
#include "Helpers/Binding.hpp"

using namespace godot;

void Game::DirectionArrow::_ready() {
  const float_t offset = get_parent_control()->get_size().y / 2.0f;
  set_pivot_offset(Vector2(offset, offset));

  DisplayDefault();

  call_deferred("_late_ready");
}

void Game::DirectionArrow::LateReady() {
  switch (direction) {
    case Down:
      set_flip_v(true);
      break;
    case Left:
      // TODO: Find a better way to wait for the node to be ready to set the rotation
      call_deferred("set_rotation_degrees", -90);
      break;
    case Right:
      // TODO: Find a better way to wait for the node to be ready to set the rotation
      call_deferred("set_rotation_degrees", 90);
      break;
    default:
      break;
  }
}

void Game::DirectionArrow::DisplayDefault() const {
  ChangeColor(defaultColor);
}

void Game::DirectionArrow::DisplayCorrect() const {
  ChangeColor(correctColor);
}

void Game::DirectionArrow::DisplayError() const {
  ChangeColor(errorColor);
}

void Game::DirectionArrow::ChangeColor(const Color& color) const {
  if (const Ref<ShaderMaterial> shaderMaterial = get_material(); shaderMaterial.is_valid()) {
    shaderMaterial->set_shader_parameter("color", color);
  } else {
    ERR_PRINT("The material is not a ShaderMaterial.");
  }
}

void Game::DirectionArrow::_bind_methods() {
  BIND_PROPERTY(Variant::COLOR, "default_color", GetDefaultColor, SetDefaultColor, PROPERTY_HINT_COLOR_NO_ALPHA, "")
  BIND_PROPERTY(Variant::COLOR, "correct_color", GetCorrectColor, SetCorrectColor, PROPERTY_HINT_COLOR_NO_ALPHA, "")
  BIND_PROPERTY(Variant::COLOR, "error_color", GetErrorColor, SetErrorColor, PROPERTY_HINT_COLOR_NO_ALPHA, "")

  ClassDB::bind_method(D_METHOD("_late_ready"), &DirectionArrow::LateReady);
}
