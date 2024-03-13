#pragma once

#include "../common/types.h"

CPP_GUARD_S

#include <stdio.h> 

#include "../common/types.h"

typedef struct joypadlist_t {
    u32 id;
    FILE *file;
    struct joypadlist_t *next;
} joypadlist_t;

CPP_GUARD_E