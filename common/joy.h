#pragma once

#include <stddef.h>

#include "defines.h"
#include "types.h"

CPP_GUARD_S

// Holds a failable result.
// ok is always 0.
typedef STR_RESULT(size_t) failable_t;

// Initialized the library.
PUB failable_t CALL joy_Init();

// Pumps events.
PUB failable_t CALL joy_PumpEvents();

CPP_GUARD_E
