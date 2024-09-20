#include "unit_test.h"

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
    REGISTER_TEST(test_addition);
    REGISTER_TEST(test_subtraction);
    RUN_TESTS();
    return 0;
}
