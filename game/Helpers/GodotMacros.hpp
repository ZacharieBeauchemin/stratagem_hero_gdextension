#pragma once

// VARIANT_ENUM_CAST macro implementation to support enum class
#define VARIANT_ENUM_CLASS_CAST(m_enum)                                                                               \
MAKE_ENUM_TYPE_INFO(m_enum)                                                                                           \
template<>                                                                                                            \
  struct VariantCaster<m_enum> {                                                                                      \
    static _FORCE_INLINE_ m_enum cast(const Variant& p_variant) {                                                     \
      return static_cast<m_enum>(p_variant.operator int64_t());                                                       \
    }                                                                                                                 \
  };                                                                                                                  \
                                                                                                                      \
template<>                                                                                                            \
struct PtrToArg<m_enum> {                                                                                             \
  _FORCE_INLINE_ static m_enum convert(const void* p_ptr) {                                                           \
    return static_cast<m_enum>(*static_cast<const int64_t*>(p_ptr));                                                  \
  }                                                                                                                   \
                                                                                                                      \
  typedef int64_t EncodeT;                                                                                            \
  _FORCE_INLINE_ static void encode(m_enum p_val, void* p_ptr) {                                                      \
    *static_cast<int64_t*>(p_ptr) = static_cast<int64_t>(p_val);                                                      \
  }                                                                                                                   \
};

// Redefined and combined MAKE_TYPED_ARRAY and MAKE_TYPED_ARRAY_INFO macros
#define MAKE_TYPED_ARRAY_WITH_INFO(m_type, m_variant_type)                                                            \
template<>                                                                                                            \
class TypedArray<m_type> : public Array {                                                                             \
public:                                                                                                               \
  _FORCE_INLINE_ TypedArray& operator=(const Array& p_array) {                                                        \
    ERR_FAIL_COND_V_MSG(!is_same_typed(p_array), *this, "Cannot assign an array with a different element type.");     \
    Array::operator=(p_array);                                                                                        \
    return *this;                                                                                                     \
  }                                                                                                                   \
                                                                                                                      \
  _FORCE_INLINE_ TypedArray(const Variant& p_variant) : TypedArray(Array(p_variant)) {}                               \
  _FORCE_INLINE_ TypedArray(const Array& p_array) {                                                                   \
    set_typed(m_variant_type, StringName(), Variant());                                                               \
    if (is_same_typed(p_array)) {                                                                                     \
      Array::operator=(p_array);                                                                                      \
    } else {                                                                                                          \
      assign(p_array);                                                                                                \
    }                                                                                                                 \
  }                                                                                                                   \
                                                                                                                      \
  _FORCE_INLINE_ TypedArray() {                                                                                       \
    set_typed(m_variant_type, StringName(), Variant());                                                               \
  }                                                                                                                   \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct GetTypeInfo<TypedArray<m_type>> {                                                                              \
  static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;                              \
  static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;       \
                                                                                                                      \
  static PropertyInfo get_class_info() {                                                                              \
    return make_property_info(                                                                                        \
      Variant::Type::ARRAY,                                                                                           \
      "",                                                                                                             \
      PROPERTY_HINT_ARRAY_TYPE,                                                                                       \
      Variant::get_type_name(m_variant_type).utf8().get_data());                                                      \
  }                                                                                                                   \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct GetTypeInfo<const TypedArray<m_type>&> {                                                                       \
  static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;                              \
  static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;       \
                                                                                                                      \
  static PropertyInfo get_class_info() {                                                                              \
    return make_property_info(                                                                                        \
      Variant::Type::ARRAY,                                                                                           \
      "",                                                                                                             \
      PROPERTY_HINT_ARRAY_TYPE,                                                                                       \
      Variant::get_type_name(m_variant_type).utf8().get_data());                                                      \
  }                                                                                                                   \
};
