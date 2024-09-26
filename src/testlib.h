#ifndef TESTLIB_H
#define TESTLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern int test_verbosity;

#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"

typedef struct TestNode {
    const char* name;
    void (*function)(void);
    bool passed;
    char* failure_message;
    struct TestNode* next;
} TestNode;

typedef struct {
    int total;
    int passed;
    int failed;
} TestStats;

#define ASSERT_TRUE(condition) \
    do { \
        current_test->passed = (condition); \
        if (!current_test->passed) { \
            asprintf(&current_test->failure_message, "%s:%d: Assertion '%s' failed.", \
                    __FILE__, __LINE__, #condition); \
            return; \
        } \
    } while (0)

#define ASSERT_FALSE(condition) \
    do { \
        current_test->passed = !(condition); \
        if (!current_test->passed) { \
            asprintf(&current_test->failure_message, "%s:%d: Assertion '!(%s)' failed.", \
                    __FILE__, __LINE__, #condition); \
            return; \
        } \
    } while (0)

#define ASSERT_EQUAL(expected, actual) \
    do { \
        current_test->passed = ((expected) == (actual)); \
        if (!current_test->passed) { \
            asprintf(&current_test->failure_message, "%s:%d: Expected %d, got %d.", \
                    __FILE__, __LINE__, (expected), (actual)); \
            return; \
        } \
    } while (0)

#define ASSERT_NOT_EQUAL(expected, actual) \
    do { \
        current_test->passed = ((expected) != (actual)); \
        if (!current_test->passed) { \
            asprintf(&current_test->failure_message, "%s:%d: Expected not %d, but got %d.", \
                    __FILE__, __LINE__, (expected), (actual)); \
            return; \
        } \
    } while (0)

#define ASSERT_NULL(pointer) \
    do { \
        current_test->passed = ((pointer) == NULL); \
        if (!current_test->passed) { \
            asprintf(&current_test->failure_message, "%s:%d: Expected NULL, but got %p.", \
                    __FILE__, __LINE__, (void *)(pointer)); \
            return; \
        } \
    } while (0)

#define ASSERT_NOT_NULL(pointer) \
    do { \
        current_test->passed = ((pointer) != NULL); \
        if (!current_test->passed) { \
            asprintf(&current_test->failure_message, "%s:%d: Expected not NULL, but got NULL.", \
                    __FILE__, __LINE__); \
            return; \
        } \
    } while (0)

#define ASSERT_STRING_EQUAL(expected, actual) \
    do { \
        current_test->passed = (strcmp((expected), (actual)) == 0); \
        if (!current_test->passed) { \
            asprintf(&current_test->failure_message, "%s:%d: Expected '%s', but got '%s'.", \
                    __FILE__, __LINE__, (expected), (actual)); \
            return; \
        } \
    } while (0)

#define ASSERT_STRING_NOT_EQUAL(expected, actual) \
    do { \
        current_test->passed = (strcmp((expected), (actual)) != 0); \
        if (!current_test->passed) { \
            asprintf(&current_test->failure_message, "%s:%d: Expected not '%s', but got '%s'.", \
                    __FILE__, __LINE__, (expected), (actual)); \
            return; \
        } \
    } while (0)

void register_test(const char *test_name, void (*test_function)(void));
TestStats run_tests(void);
void print_test_report(const TestStats* stats);

extern TestNode* current_test;

#endif // TESTLIB_H
