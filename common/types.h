#pragma once
#include "defines.h"
CPP_GUARD_S

#include <stdbool.h>

#define OPTION(TValue) struct { bool ok; TValue value; }
#define OPTION_OK(TOpt, TValue) (TOpt) { .ok=true, .value=TValue }
#define OPTION_ERR(TOpt) (TOpt) { .ok=false }

#define RESULT(TOk, TErr) struct { bool ok; union { TOk ok; TErr err; } value; }
#define RESULT_OK(TRes, TOk) (TRes) { .ok=true, .value={ .ok=TOk } }
#define RESULT_ERR(TRes, TErr) (TRes) { .ok=false, .value={ .err=TErr } }

CPP_GUARD_E
