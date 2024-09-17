// unit_test.h
#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdio.h>
#include <stdlib.h>

#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"

// Macros for assertions
#define ASSERT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, COLOR_RED "[FAIL] %s:%d: Assertion '%s' failed.\n" COLOR_RESET, \
                    __FILE__, __LINE__, #condition); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define ASSERT_EQUAL(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            fprintf(stderr, COLOR_RED "[FAIL] %s:%d: Expected %d, got %d.\n" COLOR_RESET, \
                    __FILE__, __LINE__, (expected), (actual)); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

// Macro to define a test case
#define TEST_CASE(name) static void name(void)

#define RUN_TEST(test_name) \
    do { \
        printf("[RUN ] %s\n", #test_name); \
        test_name(); \
        printf(COLOR_GREEN "[PASS] %s\n\n" COLOR_RESET, #test_name); \
    } while (0)

#endif // UNIT_TEST_H
