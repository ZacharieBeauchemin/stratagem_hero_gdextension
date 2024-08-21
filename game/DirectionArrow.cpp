//
// Created by Zach on 2024-08-17.
//

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/shader_material.hpp>

#include "DirectionArrow.hpp"

using namespace godot;

namespace Game {
  void DirectionArrow::_ready() {
    const float_t offset = get_parent_control()->get_size().y / 2.0f;
    set_pivot_offset(Vector2(offset, offset));

    DisplayDefault();

    call_deferred("_late_ready");
  }

  void DirectionArrow::LateReady() {
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

  void DirectionArrow::DisplayDefault() const {
    ChangeColor(defaultColor);
  }

  void DirectionArrow::DisplayCorrect() const {
    ChangeColor(correctColor);
  }

  void DirectionArrow::DisplayError() const {
    ChangeColor(errorColor);
  }

  void DirectionArrow::ChangeColor(const Color& color) const {
    if (const Ref<ShaderMaterial> shaderMaterial = get_material(); shaderMaterial.is_valid()) {
      shaderMaterial->set_shader_parameter("color", color);
    } else {
      ERR_PRINT("The material is not a ShaderMaterial.");
    }
  }

  void DirectionArrow::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_default_color", "default_color"), &DirectionArrow::SetDefaultColor);
    ClassDB::bind_method(D_METHOD("get_default_color"), &DirectionArrow::GetDefaultColor);
    ADD_PROPERTY(
      PropertyInfo(Variant::COLOR, "default_color", PROPERTY_HINT_COLOR_NO_ALPHA, ""),
      "set_default_color",
      "get_default_color");

    ClassDB::bind_method(D_METHOD("set_correct_color", "correct_color"), &DirectionArrow::SetCorrectColor);
    ClassDB::bind_method(D_METHOD("get_correct_color"), &DirectionArrow::GetCorrectColor);
    ADD_PROPERTY(
      PropertyInfo(Variant::COLOR, "correct_color", PROPERTY_HINT_COLOR_NO_ALPHA, ""),
      "set_correct_color",
      "get_correct_color");

    ClassDB::bind_method(D_METHOD("set_error_color", "error_color"), &DirectionArrow::SetErrorColor);
    ClassDB::bind_method(D_METHOD("get_error_color"), &DirectionArrow::GetErrorColor);
    ADD_PROPERTY(
      PropertyInfo(Variant::COLOR, "error_color", PROPERTY_HINT_COLOR_NO_ALPHA, ""),
      "set_error_color",
      "get_error_color");

    ClassDB::bind_method(D_METHOD("_late_ready"), &DirectionArrow::LateReady);
  }
}
