#include "testlib.h"

static void test_true(void) {
    ASSERT_TRUE(1);
}

static void test_false(void) {
    ASSERT_FALSE(0);
}

static void test_equal(void) {
    ASSERT_EQUAL(1, 1);
}

static void test_not_equal(void) {
    ASSERT_NOT_EQUAL(0, 1);
}

static void test_null(void) {
    ASSERT_NULL(NULL);
}

static void test_not_null(void) {
    ASSERT_NOT_NULL((void *)1);
}

static void test_string_equal(void) {
    ASSERT_STRING_EQUAL("Hello", "Hello");
}

static void test_string_not_equal(void) {
    ASSERT_STRING_NOT_EQUAL("Hello", "World");
}

int main() {
    test_verbosity = 0;
    register_test("test_true", test_true);
    register_test("test_false", test_false);
    register_test("test_equal", test_equal);
    register_test("test_not_equal", test_not_equal);
    register_test("test_null", test_null);
    register_test("test_not_null", test_not_null);
    register_test("test_string_equal", test_string_equal);
    register_test("test_string_not_equal", test_string_not_equal);
    run_tests();

    return 0;
}
