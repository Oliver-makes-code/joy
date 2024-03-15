#include "joy.h"
#include "types.h"

failable_usize CALL joy_Init() {
    return RESULT_OK(failable_usize, 0);
}

failable_usize CALL joy_PumpEvents() {
    return RESULT_OK(failable_usize, 0);
}
