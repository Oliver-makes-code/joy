#pragma once

#include "../common/defines.h"

CPP_GUARD_S

#include "../common/joy.h"

// Enumerates and opens gamepads (on evdev interface)
failable_usize joy_linux_evdev_EnumerateDevices();

CPP_GUARD_E
