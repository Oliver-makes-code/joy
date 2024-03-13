#include "../common/platform_private.h"
#include "evdev.h"
#include "jsdev.h"

void joy_platform_EnumerateDevices() {
    joy_linux_evdev_EnumerateDevices();
    joy_linux_jsdev_EnumerateDevices();
}
