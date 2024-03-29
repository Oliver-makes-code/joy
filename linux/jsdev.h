#pragma once

#include "../common/joy.h"

CPP_GUARD_S

#include <stdbool.h>

// Confirms that a file path is a gamepad (on jsdev interface)
bool joy_linux_jsdev_IsGamepad(const char *path);

// Enumerates and opens gamepads (on jsdev interface)
failable_usize joy_linux_jsdev_EnumerateDevices();

CPP_GUARD_E
