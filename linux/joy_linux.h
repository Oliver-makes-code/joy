#pragma once

#include "../common/defines.h"

CPP_GUARD_S

#include <stdio.h> 

#include "../common/types.h"

typedef struct {
    u32 id;
    FILE *file;
} joypadfile_t;

typedef OPTION(joypadfile_t) option_joypadfile_t;

typedef struct {
    usize length;
    usize capacity;
    option_joypadfile_t *data;
} joypadlist_t;

failable_usize joy_linux_joypadlist_AddJoypad(joypadlist_t *list, u32 id, FILE *file);
bool joy_linux_joypadlist_HasJoypad(joypadlist_t *list, u32 id);
failable_usize joy_linux_joypadlist_RemoveJoypad(joypadlist_t *list, u32 id);

CPP_GUARD_E
