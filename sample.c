#include "unit_test.h"

TEST_CASE(test_addition) {
    int result = 2 + 2;
    ASSERT_EQUAL(4, result);
}

TEST_CASE(test_subtraction) {
    int result = 2 - 2;
    ASSERT_EQUAL(0, result);
}

int main() {
    RUN_TEST(test_addition);
    RUN_TEST(test_subtraction);
    return 0;
}
