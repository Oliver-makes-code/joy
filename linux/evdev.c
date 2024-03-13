#include <dirent.h>
#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <linux/input.h>

#include "evdev.h"
#include "joy_linux.h"

joypadlist_t *joy_linux_evdev_joypadlist = 0;

bool joy_linux_evdev_HasJoypad(u32 id) {
    joypadlist_t *current = joy_linux_evdev_joypadlist;

    // Iterate through the list and check if the ID matches.
    // It might make more sense to use a hashset for this.
    // Currently it will cause an infinite loop if the list loops in on itself.
    while (current) {
        if (current->id == id)
            return true;
        current = current->next;
    }
    return false;
}

void joy_linux_evdev_AddJoypad(u32 id, FILE *file) {
    // Create a new node and add it to the list
    joypadlist_t *node = malloc(sizeof(joypadlist_t));
    node->id = id;
    node->file = file;
    node->next = joy_linux_evdev_joypadlist;
    joy_linux_evdev_joypadlist = node;
}

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

void joy_linux_evdev_EnumerateDevices() {
    const char *lin_SearchPath = "/dev/input";

    DIR *d;
    struct dirent *dir;
    d = opendir(lin_SearchPath);
    size_t len = strlen(lin_SearchPath);

    if (!d)
        return;

    while ((dir = readdir(d))) {
        char *d_name = dir->d_name;
        // Ignore parent and current dirs
        if (!strcmp(d_name, "."))
            continue;
        if (!strcmp(d_name, ".."))
            continue;
        if (strncmp(d_name, "event", 5))
            continue;

        u32 id = 0;

        sscanf(d_name, "event%u", &id);

        // Continue if the joypad already exists
        if (joy_linux_evdev_HasJoypad(id))
            continue;

        // Calculate the length of the full name
        size_t dirlen = strlen(d_name);
        size_t size = (len+dirlen+2);

        // Allocate a string of the length of the full name
        char *filename = malloc(size);
        if (filename == NULL) 
            continue;

        // Concat the paths
        sprintf(filename, "%s/%s", lin_SearchPath, dir->d_name);
        
        // Open the file and check if it's a joypad
        FILE *file = fopen(filename, "rw"); // Past this point we have a pointer and file we need to clean up. Continuing should goto fail.

        if (!joy_linux_evdev_IsJoypad(file))
            goto fail;

        // Add joypad
        joy_linux_evdev_AddJoypad(id, file);

        free(filename);
        continue;

      fail:
        free(filename);
        fclose(file);
    }
    closedir(d);
}
