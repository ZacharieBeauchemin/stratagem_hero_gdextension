//
// Created by Zach on 2024-08-17.
//

#pragma once

#include <godot_cpp/classes/texture_rect.hpp>

#include "Resources/Direction.hpp"

namespace Game {
  class DirectionArrow final : public godot::TextureRect {
    GDCLASS(DirectionArrow, TextureRect)

  private:
    Direction direction = Up;
    godot::Color defaultColor;
    godot::Color correctColor;
    godot::Color errorColor;

  public:
    void _ready() override;

    void DisplayDefault() const;
    void DisplayCorrect() const;
    void DisplayError() const;

    void SetDirection(const Direction direction) { this->direction = direction; }
    [[nodiscard]] Direction GetDirection() const { return direction; }

    void SetDefaultColor(const godot::Color& defaultColor) { this->defaultColor = defaultColor; }
    [[nodiscard]] godot::Color GetDefaultColor() const { return defaultColor; }

    void SetCorrectColor(const godot::Color& correctColor) { this->correctColor = correctColor; }
    [[nodiscard]] godot::Color GetCorrectColor() const { return correctColor; }

    void SetErrorColor(const godot::Color& errorColor) { this->errorColor = errorColor; }
    [[nodiscard]] godot::Color GetErrorColor() const { return errorColor; }

  protected:
    static void _bind_methods();

  private:
    void LateReady();

    void ChangeColor(const godot::Color& color) const;
  };
}
