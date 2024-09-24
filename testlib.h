#ifndef TESTLIB_H
#define TESTLIB_H

#include <stdio.h>
#include <stdlib.h>

extern int test_verbosity;

#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"

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

#define TEST_CASE(name) void name(void)

void register_test(const char *test_name, void (*test_function)(void));
void run_tests(void);

#endif // TESTLIB_H
