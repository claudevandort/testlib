#ifndef TESTLIB_H
#define TESTLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define ASSERT_FALSE(condition) \
    do { \
        if ((condition)) { \
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

#define ASSERT_NOT_EQUAL(expected, actual) \
    do { \
        if ((expected) == (actual)) { \
            fprintf(stderr, COLOR_RED "[FAIL] %s:%d: Expected not %d, but got %d.\n" COLOR_RESET, \
                    __FILE__, __LINE__, (expected), (actual)); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define ASSERT_NULL(pointer) \
    do { \
        if ((pointer) != NULL) { \
            fprintf(stderr, COLOR_RED "[FAIL] %s:%d: Expected NULL, but got %p.\n" COLOR_RESET, \
                    __FILE__, __LINE__, (void *)(pointer)); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define ASSERT_NOT_NULL(pointer) \
    do { \
        if ((pointer) == NULL) { \
            fprintf(stderr, COLOR_RED "[FAIL] %s:%d: Expected not NULL, but got NULL.\n" COLOR_RESET, \
                    __FILE__, __LINE__); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define ASSERT_STRING_EQUAL(expected, actual) \
    do { \
        if (strcmp((expected), (actual)) != 0) { \
            fprintf(stderr, COLOR_RED "[FAIL] %s:%d: Expected '%s', but got '%s'.\n" COLOR_RESET, \
                    __FILE__, __LINE__, (expected), (actual)); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define ASSERT_STRING_NOT_EQUAL(expected, actual) \
    do { \
        if (strcmp((expected), (actual)) == 0) { \
            fprintf(stderr, COLOR_RED "[FAIL] %s:%d: Expected not '%s', but got '%s'.\n" COLOR_RESET, \
                    __FILE__, __LINE__, (expected), (actual)); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

void register_test(const char *test_name, void (*test_function)(void));
void run_tests(void);

#endif // TESTLIB_H
