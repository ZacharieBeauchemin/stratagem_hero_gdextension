#pragma once

#define BIND_PROPERTY(variant_type, property_name, getter_name, setter_name, hint_type, hint_string)                  \
{                                                                                                                     \
  String snake_case_property_name = StringName(property_name).to_snake_case();                                        \
  ClassDB::bind_method(D_METHOD("set_" + snake_case_property_name, property_name), setter_name);                      \
  ClassDB::bind_method(D_METHOD("get_" + snake_case_property_name), getter_name);                                     \
  ADD_PROPERTY(                                                                                                       \
    PropertyInfo(variant_type, snake_case_property_name, hint_type, hint_string),                                     \
    "set_" + snake_case_property_name,                                                                                \
    "get_" + snake_case_property_name                                                                                 \
  );                                                                                                                  \
}

#define BIND_ARRAY_PROPERTY(property_name, getter_name, setter_name, hint_string)                                     \
BIND_PROPERTY(Variant::ARRAY, property_name, getter_name, setter_name, PROPERTY_HINT_TYPE_STRING, hint_string)

#define BIND_COLOR_PROPERTY(property_name, getter_name, setter_name)                                                  \
BIND_PROPERTY(Variant::COLOR, property_name, getter_name, setter_name, PROPERTY_HINT_COLOR_NO_ALPHA, "")

#define BIND_OBJECT_PROPERTY(property_name, getter_name, setter_name, hint_string)                                    \
BIND_PROPERTY(Variant::OBJECT, property_name, getter_name, setter_name, PROPERTY_HINT_NODE_TYPE, "")
