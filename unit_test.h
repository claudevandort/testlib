// unit_test.h
#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdio.h>
#include <stdlib.h>

static int test_verbosity = 1;

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

// Dynamic arrays for test functions and names
static void (**test_functions)(void) = NULL;
static const char** test_names = NULL;
static int test_count = 0;
static int test_capacity = 0;

// Macro to register a test
#define REGISTER_TEST(test_name) \
    do { \
        if (test_count >= test_capacity) { \
            /* Increase capacity */ \
            test_capacity = test_capacity == 0 ? 10 : test_capacity * 2; \
            /* Reallocate memory for test_functions */ \
            void (**new_functions)(void) = realloc(test_functions, test_capacity * sizeof(void (*)(void))); \
            if (!new_functions) { \
                fprintf(stderr, "Failed to allocate memory for test functions.\n"); \
                exit(EXIT_FAILURE); \
            } \
            test_functions = new_functions; \
            /* Reallocate memory for test_names */ \
            const char** new_names = realloc(test_names, test_capacity * sizeof(const char*)); \
            if (!new_names) { \
                fprintf(stderr, "Failed to allocate memory for test names.\n"); \
                exit(EXIT_FAILURE); \
            } \
            test_names = new_names; \
        } \
        test_functions[test_count] = test_name; \
        test_names[test_count] = #test_name; \
        test_count++; \
    } while (0)

// Function to run all registered tests
static void RUN_TESTS(void) {
    for (int i = 0; i < test_count; ++i) {
        if (test_verbosity == 0) {
            test_functions[i]();
            printf(COLOR_GREEN "." COLOR_RESET);
        } else {
            printf("[RUN ] %s\n", test_names[i]);
            test_functions[i]();
            printf(COLOR_GREEN "[PASS] %s\n\n" COLOR_RESET, test_names[i]);
        }
    }
    if (test_verbosity == 0) {
        printf("\n");
    }
    /* Free allocated memory */
    free(test_functions);
    free(test_names);
    test_functions = NULL;
    test_names = NULL;
    test_count = 0;
    test_capacity = 0;
}

#endif // UNIT_TEST_H
