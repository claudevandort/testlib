#include "testlib.h"

static void test_addition(void) {
    int result = 2 + 2;
    ASSERT_EQUAL(4, result);
}

static void test_subtraction(void) {
    int result = 2 - 2;
    ASSERT_EQUAL(0, result);
}

int main() {
    test_verbosity = 0;
    register_test("test_addition", test_addition);
    register_test("test_subtraction", test_subtraction);
    run_tests();

    return 0;
}
