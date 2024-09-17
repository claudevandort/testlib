// unit_test.c
#include "unit_test.h"

void run_test(void (*test)(), const char* test_name) {
    printf("Running test: %s\n", test_name);
    test();
    printf("Test %s passed.\n", test_name);
}

// Implement ASSERT_TRUE, ASSERT_EQUAL, etc.
