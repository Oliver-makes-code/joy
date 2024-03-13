#include "joy.h"
#include "types.h"

int CALL add(int a, int b) {
    return a + b;
}

typedef STR_RESULT(int) test_t;

test_t test() {
    return RESULT_ERR(test_t, "nya :3");
}
