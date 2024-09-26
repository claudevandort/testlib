#include "testlib.h"

static void test_true(TestNode* test) {
    ASSERT_TRUE(1);
}

static void test_false(TestNode* test) {
    ASSERT_FALSE(0);
}

static void test_equal(TestNode* test) {
    ASSERT_EQUAL(1, 1);
}

static void test_not_equal(TestNode* test) {
    ASSERT_NOT_EQUAL(0, 1);
}

static void test_null(TestNode* test) {
    ASSERT_NULL(NULL);
}

static void test_not_null(TestNode* test) {
    ASSERT_NOT_NULL((void *)1);
}

static void test_string_equal(TestNode* test) {
    ASSERT_STRING_EQUAL("Hello", "Hello");
}

static void test_string_not_equal(TestNode* test) {
    ASSERT_STRING_NOT_EQUAL("Hello", "World");
}

int main() {
    test_verbosity = 0;
    TestSuite* suite1 = create_test_suite("Suite 1");
    TestSuite* suite2 = create_test_suite("Suite 2");
    register_test(suite1, "test_true", test_true);
    register_test(suite1, "test_false", test_false);
    register_test(suite1, "test_equal", test_equal);
    register_test(suite1, "test_not_equal", test_not_equal);
    register_test(suite2, "test_null", test_null);
    register_test(suite2, "test_not_null", test_not_null);
    register_test(suite2, "test_string_equal", test_string_equal);
    register_test(suite2, "test_string_not_equal", test_string_not_equal);
    run_tests();
    TestStats* stats = make_test_report();
    return stats->failed;
}
