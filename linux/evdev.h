#pragma once
#include "../common/joy.h"

CPP_GUARD_S

// Confirms that a file path is a gamepad (on evdev interface)
bool joy_linux_evdev_IsGamepad(const char *path);

// Enumerates and opens gamepads (on evdev interface)
void joy_linux_evdev_EnumerateDevices();

CPP_GUARD_E