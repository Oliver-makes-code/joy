#pragma once

#include "defines.h"

CPP_GUARD_S

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "errors.h"

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

#define FAILABLE(TOk) RESULT(TOk, error_t)

// Holds a failable result.
typedef FAILABLE(usize) failable_usize;
typedef FAILABLE(FILE *) failable_FILE;

typedef OPTION(f32) option_f32;
typedef OPTION(u16) option_u16;
typedef OPTION(bool) option_bool;
typedef OPTION(usize) option_usize;

// Holds info about a joypad.
// TODO: sensors? rumble?
typedef struct {
    // The ID of the joypad.
    u32 id;
    // The number of buttons on the joypad
    u16 button_count;
    // The number of axes on the joypad
    u16 axis_count;
} joypadinfo_t;

typedef OPTION(joypadinfo_t) option_joypadinfo_t;

CPP_GUARD_E
