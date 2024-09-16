//
// Created by Zach on 2024-09-15.
//

#pragma once

#define CONNECT_SIGNAL(object, signalName, method)                  \
if (object->connect(signalName, callable_mp(this, method)) != OK) { \
  ERR_PRINT("Failed to connect " signalName " signal.");            \
}
