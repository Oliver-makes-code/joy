#include <dirent.h>
#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <linux/input.h>

#include "evdev.h"
#include "joy_linux.h"

const error_t joy_linux_evdev_error_nodir = {
    .err = FILE_NOEXISTS,
    .msg = "/dev/input Doesn't Exist"
};

const char *joy_linux_evdev_search_path = "/dev/input";
const int joy_linux_evdev_search_path_len = 10;

joypadlist_t joy_linux_evdev_joypadlist = {0, 0, 0};

bool joy_linux_evdev_IsJoypad(FILE *file) {
    // Get the file descriptor
    int fd = fileno(file);

    // We should have a descriptor, but it's always good to check.
    if (fd == -1)
        return false;

    // Grab the input
    struct input_id id;
    if (ioctl(fd, EVIOCGID, &id) == -1)
        return false;

    if (id.bustype != BUS_USB && id.bustype != BUS_BLUETOOTH)
        return false;

    // We can probably assume it's a gamepad here. Might wanna do some further testing.

    return true;
}

bool joy_linux_evdev_IsValidDevice(const char *name) {
    if (!strcmp(name, "."))
        return false;
    if (!strcmp(name, ".."))
        return false;
    if (strncmp(name, "event", 5))
        return false;
    return true;
}

u32 joy_linux_evdev_GetJoypadId(const char *name) {
    u32 id = 0;

    sscanf(name, "event%u", &id);

    return id;
}

failable_FILE joy_linux_evdev_OpenEventFile(const char* name) {

    // Calculate the length of the full name
    size_t size = (joy_linux_evdev_search_path_len+strlen(name)+2);

    // Allocate a string of the length of the full name
    char *filename = malloc(size);
    if (filename == NULL) 
        return RESULT_ERR(failable_FILE, joy_error_malloc_failed);
    
    // Concat the paths
    sprintf(filename, "%s/%s", joy_linux_evdev_search_path, name);
    
    // Open the file and check if it's a joypad
    FILE *file = fopen(filename, "rw");

    // Free the file name
    free(filename);

    return RESULT_OK(failable_FILE, file);
}

failable_usize joy_linux_evdev_EnumerateDevices() {
    DIR *d;
    struct dirent *dir;
    d = opendir(joy_linux_evdev_search_path);
    size_t len = strlen(joy_linux_evdev_search_path);

    if (!d)
        return RESULT_ERR(failable_usize, joy_linux_evdev_error_nodir);

    while ((dir = readdir(d))) {
        char *d_name = dir->d_name;
        // Ignore parent and current dirs
        if (!joy_linux_evdev_IsValidDevice(d_name))
            continue;

        u32 id = joy_linux_evdev_GetJoypadId(d_name);

        // Continue if the joypad already exists
        if (joy_linux_joypadlist_HasJoypad(&joy_linux_evdev_joypadlist, id))
            continue;

        failable_FILE file_result = joy_linux_evdev_OpenEventFile(d_name);

        // Cascade error
        if (!file_result.ok) {
            closedir(d);
            return RESULT_ERR(failable_usize, file_result.value.err);
        }

        FILE *file = file_result.value.ok;

        if (!joy_linux_evdev_IsJoypad(file)) {
            fclose(file);
            continue;
        }

        // Add joypad
        failable_usize result = joy_linux_joypadlist_AddJoypad(&joy_linux_evdev_joypadlist, id, file);

        // Cascade error
        if (!result.ok) {
            fclose(file);
            closedir(d);
            return result;
        }

        continue;
    }

    closedir(d);
    return RESULT_OK(failable_usize, 0);
}
