#pragma once

#include "defines.h"

CPP_GUARD_S

typedef enum {
    MALLOC_FAILED,
    ELEMENT_EXISTS,
    ELEMENT_NOEXISTS,
    FILE_NOEXISTS,
} errno_t;

typedef struct {
    errno_t err;
    const char *msg;
} error_t;

extern const error_t joy_error_malloc_failed;

extern const error_t joy_error_element_exists;

extern const error_t joy_error_element_noexists;

CPP_GUARD_E
