#pragma once


#include "defines.h"

CPP_GUARD_S

#include <stddef.h>

#include "types.h"

// Initializes the library.
PUB failable_t CALL joy_Init();

// Pumps events.
PUB failable_t CALL joy_PumpEvents();

// Gets the info of a joypad.
// Returns ok=false if not connected.
PUB option_joypadinfo_t CALL joy_GetJoypadInfo(u32 id);

PUB option_f32 CALL joy_GetAxis(u32 id, u32 axis);
PUB option_bool CALL joy_GetButton(u32 id, u32 button);

CPP_GUARD_E
