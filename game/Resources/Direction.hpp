#pragma once

#include "../Helpers/GodotMacros.hpp"

namespace Game {
	enum class Direction {
		Up,
		Down,
		Left,
		Right
	};

	constexpr const char* DirectionToString(const Direction direction) {
		using enum Direction;

		switch (direction) {
			case Up: return "Up";
			case Down: return "Down";
			case Left: return "Left";
			case Right: return "Right";
			default: return "Invalid";
		}
	}
}

namespace godot {
	VARIANT_ENUM_CLASS_CAST(Game::Direction)

	MAKE_TYPED_ARRAY_WITH_INFO(Game::Direction, godot::Variant::INT)
}
