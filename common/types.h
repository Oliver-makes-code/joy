#pragma once

#include "defines.h"

CPP_GUARD_S

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef double f64;
typedef float f32;

typedef size_t usize;
typedef ptrdiff_t isize;
typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint8_t u8;
typedef int8_t i8;

#define OPTION(TValue) struct { bool ok; TValue value; }
#define OPTION_OK(TOpt, TValue) (TOpt) { .ok=true, .value=TValue }
#define OPTION_ERR(TOpt) (TOpt) { .ok=false }

#define RESULT(TOk, TErr) struct { bool ok; union { TOk ok; TErr err; } value; }
#define RESULT_OK(TRes, TOk) (TRes) { .ok=true, .value={ .ok=TOk } }
#define RESULT_ERR(TRes, TErr) (TRes) { .ok=false, .value={ .err=TErr } }

#define STR_RESULT(TOk) RESULT(TOk, char *)

// Holds a failable result.
// ok is always 0.
typedef STR_RESULT(usize) failable_t;

typedef struct {
    u32 id;
} joypadinfo_t;

typedef OPTION(joypadinfo_t) option_joypadinfo_t;

CPP_GUARD_E
