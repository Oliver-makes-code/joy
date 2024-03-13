#include "../common/platform_private.h"
#include "evdev.h"
#include "jsdev.h"

void platform_EnumerateDevices() {
    linux_evdev_EnumerateDevices();
    linux_jsdev_EnumerateDevices();
}
