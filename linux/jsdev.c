#include <stdbool.h>

#include "jsdev.h"

bool joy_linux_jsdev_IsGamepad(const char *path) {
    // Not implemented.
    return false;
}

failable_usize joy_linux_jsdev_EnumerateDevices() {
    // Not implemented.
    return RESULT_OK(failable_usize, 0);
}
