//
// Created by Zach on 2024-09-15.
//

#pragma once

#define BIND_PROPERTY(variant_type, property_name, getter_name, setter_name, hint, hint_string)   \
{                                                                                                 \
  String snake_case_property_name = StringName(property_name).to_snake_case();                    \
  ClassDB::bind_method(D_METHOD("set_" + snake_case_property_name, property_name), setter_name);  \
  ClassDB::bind_method(D_METHOD("get_" + snake_case_property_name), getter_name);                 \
  ADD_PROPERTY(                                                                                   \
    PropertyInfo(variant_type, snake_case_property_name, hint, hint_string),                      \
    "set_" + snake_case_property_name,                                                            \
    "get_" + snake_case_property_name                                                             \
  );                                                                                              \
}
