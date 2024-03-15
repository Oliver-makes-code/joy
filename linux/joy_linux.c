#include <stdlib.h>
#include <string.h>

#include "joy_linux.h"
#include "../common/platform_private.h"
#include "evdev.h"
#include "jsdev.h"

failable_usize joy_platform_EnumerateDevices() {
    failable_usize result;
    result = joy_linux_evdev_EnumerateDevices();
    if (!result.ok)
        return result;
    result = joy_linux_jsdev_EnumerateDevices();
    if (!result.ok)
        return result;

    return RESULT_OK(failable_usize, 0);
}

bool joy_linux_joypadlist_HasJoypad(joypadlist_t *list, u32 id) {
    // Iterate through the list and check if the ID matches.
    usize len = list->length;
    for (usize i = 0; i < len; i++) {
        option_joypadfile_t *file = &list->data[i];
        if (file->ok && file->value.id == id)
            return true;
    }
    return false;
}

failable_usize joy_linux_joypadlist_AddJoypad(joypadlist_t *list, u32 id, FILE *file) {
    // Break if the pad already exists.
    if (joy_linux_joypadlist_HasJoypad(list, id))
        return RESULT_ERR(failable_usize, joy_error_element_exists);
    
    joypadfile_t pad = { .id = id, .file = file };
    usize len = list->length;

    // Look for an empty slot
    option_usize open_idx = OPTION_ERR(option_usize);
    for (usize i = 0; i < len; i++) {
        option_joypadfile_t *file = &list->data[i];
        if (!file->ok) {
            open_idx = OPTION_OK(option_usize, i);
            break;
        }
    }

    // Set the empty slot if it exists
    if (open_idx.ok) {
        list->data[open_idx.value] = OPTION_OK(option_joypadfile_t, pad);
        return RESULT_OK(failable_usize, 0);
    }

    // Append the element if there's empty space in the array
    if (list->capacity > len) {
        list->data[len] = OPTION_OK(option_joypadfile_t, pad);
        list->length++;
        return RESULT_OK(failable_usize, 0);
    }

    // Create a new buffer with a larger size
    usize new_capacity = list->capacity * 2;

    if (new_capacity == 0)
        new_capacity = 4;

    option_joypadfile_t *buf = malloc(sizeof(option_joypadfile_t) * new_capacity);
    if (!buf)
        return RESULT_ERR(failable_usize, joy_error_malloc_failed);

    // Copy the buffer
    memcpy(buf, list->data, list->capacity);

    // Free the old buffer
    free(list->data);

    // Replace the buffer in the list
    list->data = buf;

    return RESULT_OK(failable_usize, 0);
}

failable_usize joy_linux_joypadlist_RemoveJoypad(joypadlist_t *list, u32 id) {
    // Iterate through the list and check if the ID matches.
    usize len = list->length;
    for (usize i = 0; i < len; i++) {
        option_joypadfile_t *file = &list->data[i];
        if (file->ok && file->value.id == id) {
            // Close the file and remove it from the list
            fclose(file->value.file);
            *file = OPTION_ERR(option_joypadfile_t);
            return RESULT_OK(failable_usize, 0);
        }
    }
    return RESULT_ERR(failable_usize, joy_error_element_noexists);
}
