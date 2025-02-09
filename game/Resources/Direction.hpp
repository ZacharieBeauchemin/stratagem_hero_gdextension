#pragma once

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
	// Expanded macro VARIANT_ENUM_CAST(Game::Direction) to support enum class
	MAKE_ENUM_TYPE_INFO(Game::Direction)

	template<>
	struct VariantCaster<Game::Direction> {
		static _FORCE_INLINE_ Game::Direction cast(const Variant& p_variant) {
			return static_cast<Game::Direction>(p_variant.operator int64_t());
		}
	};

	template<>
	struct PtrToArg<Game::Direction> {
		_FORCE_INLINE_ static Game::Direction convert(const void* p_ptr) {
			return static_cast<Game::Direction>(*static_cast<const int64_t*>(p_ptr));
		}

		typedef int64_t EncodeT;
		_FORCE_INLINE_ static void encode(Game::Direction p_val, void* p_ptr) {
			*static_cast<int64_t*>(p_ptr) = static_cast<int64_t>(p_val);
		}
	};

	// Expanded macro MAKE_TYPED_ARRAY(Game::Direction, godot::Variant::INT)
	template<>
	class TypedArray<Game::Direction> : public Array {
	public:
		_FORCE_INLINE_ void operator=(const Array& p_array) const {
			ERR_FAIL_COND_MSG(!is_same_typed(p_array), "Cannot assign an array with a different element type.");
			_ref(p_array);
		}

		_FORCE_INLINE_ TypedArray(const Variant& p_variant) : TypedArray(Array(p_variant)) {}
		_FORCE_INLINE_ TypedArray(const Array& p_array) {
			set_typed(Variant::INT, StringName(), Variant());
			if (is_same_typed(p_array)) {
				_ref(p_array);
			} else {
				assign(p_array);
			}
		}

		_FORCE_INLINE_ TypedArray() {
			set_typed(Variant::INT, StringName(), Variant());
		}
	};

	// Expanded macro MAKE_TYPED_ARRAY_INFO(Game::Direction, godot::Variant::INT)
	template<>
	struct GetTypeInfo<TypedArray<Game::Direction>> {
		static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
		static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;

		static PropertyInfo get_class_info() {
			return make_property_info(
				Variant::Type::ARRAY,
				"",
				PROPERTY_HINT_ARRAY_TYPE,
				Variant::get_type_name(Variant::INT).utf8().get_data());
		}
	};

	template<>
	struct GetTypeInfo<const TypedArray<Game::Direction>&> {
		static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
		static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;

		static PropertyInfo get_class_info() {
			return make_property_info(
				Variant::Type::ARRAY,
				"",
				PROPERTY_HINT_ARRAY_TYPE,
				Variant::get_type_name(Variant::INT).utf8().get_data());
		}
	};
}
