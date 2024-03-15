#include "errors.h"

const error_t joy_error_malloc_failed = {
    .err = MALLOC_FAILED,
    .msg = "malloc() failed."
};

const error_t joy_error_element_exists = {
    .err = ELEMENT_EXISTS,
    .msg = "Array Element Exists"
};

const error_t joy_error_element_noexists = {
    .err = ELEMENT_NOEXISTS,
    .msg = "Array Element Doesn't Exist"
};
