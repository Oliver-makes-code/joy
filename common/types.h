#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "defines.h"

CPP_GUARD_S

#define OPTION(TValue) struct { bool ok; TValue value; }
#define OPTION_OK(TOpt, TValue) (TOpt) { .ok=true, .value=TValue }
#define OPTION_ERR(TOpt) (TOpt) { .ok=false }

#define RESULT(TOk, TErr) struct { bool ok; union { TOk ok; TErr err; } value; }
#define RESULT_OK(TRes, TOk) (TRes) { .ok=true, .value={ .ok=TOk } }
#define RESULT_ERR(TRes, TErr) (TRes) { .ok=false, .value={ .err=TErr } }

#define STR_RESULT(TOk) RESULT(TOk, char*)

CPP_GUARD_E
