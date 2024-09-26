#include "testlib.h"

static TestSuite* suite_list_head = NULL;
TestNode* current_test = NULL;

int test_verbosity = 1;

TestSuite* create_test_suite(const char* suite_name) {
    TestSuite* new_suite = (TestSuite*)malloc(sizeof(TestSuite));
    if (!new_suite) {
        fprintf(stderr, "Error: Failed to allocate memory for test suite.\n");
        exit(1);
    }
    new_suite->name = suite_name;
    new_suite->tests = NULL;
    new_suite->next = NULL;

    if (!suite_list_head) {
        suite_list_head = new_suite;
    } else {
        TestSuite* current = suite_list_head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_suite;
    }
    return new_suite;
}

void register_test(TestSuite* suite, const char* test_name, void (*test_function)(TestNode*)) {
    if (!suite) {
        fprintf(stderr, "Error: Invalid test suite.\n");
        return;
    }

    TestNode* new_test = (TestNode*)malloc(sizeof(TestNode));
    if (!new_test) {
        fprintf(stderr, "Error: Failed to allocate memory for test node.\n");
        exit(1);
    }
    new_test->name = test_name;
    new_test->function = test_function;
    new_test->passed = false;
    new_test->failure_message = NULL;
    new_test->next = NULL;

    if (!suite->tests) {
        suite->tests = new_test;
    } else {
        TestNode* current = suite->tests;
        while (current->next) {
            current = current->next;
        }
        current->next = new_test;
    }
}

void run_tests(void) {
    TestSuite* current_suite = suite_list_head;

    while (current_suite) {
        // Initialize suite stats
        current_suite->stats.total = 0;
        current_suite->stats.passed = 0;
        current_suite->stats.failed = 0;

        if (test_verbosity > 0) {
            printf("\nRunning test suite: %s\n", current_suite->name);
        }

        TestNode* current_test = current_suite->tests;
        while (current_test) {
            current_test->passed = true;  // Set to true before running the test
            current_test->function(current_test);

            current_suite->stats.total++;
            if (current_test->passed) {
                current_suite->stats.passed++;
                if (test_verbosity == 0) {
                    printf(COLOR_GREEN "." COLOR_RESET);
                    fflush(stdout);
                } else if (test_verbosity > 0) {
                    printf(COLOR_GREEN "[PASS]" COLOR_RESET " %s\n", current_test->name);
                }
            } else {
                current_suite->stats.failed++;
                if (test_verbosity == 0) {
                    printf(COLOR_RED "F" COLOR_RESET);
                    fflush(stdout);
                } else if (test_verbosity > 0) {
                    printf(COLOR_RED "[FAIL]" COLOR_RESET " %s\n", current_test->name);
                    if (current_test->failure_message) {
                        printf("       %s\n", current_test->failure_message);
                    }
                }
            }

            if (test_verbosity > 1) {
                printf("\n");
            }

            // Free the failure message if it exists
            if (current_test->failure_message) {
                free(current_test->failure_message);
                current_test->failure_message = NULL;
            }

            current_test = current_test->next;
        }

        current_suite = current_suite->next;
    }
}

TestStats* make_test_report(void) {
    TestSuite* current_suite = suite_list_head;
    TestStats* total_stats = (TestStats*)malloc(sizeof(TestStats));
    if (!total_stats) {
        fprintf(stderr, "Error: Failed to allocate memory for test stats.\n");
        exit(1);
    }
    *total_stats = (TestStats) {0, 0, 0};

    printf("\nTest Report\n");
    printf("+-----------------+-------+-------+-------+----------+\n");
    printf("| Suite           | Total | Passed| Failed| Pass Rate|\n");
    printf("+-----------------+-------+-------+-------+----------+\n");

    while (current_suite) {
        float pass_rate = (current_suite->stats.total > 0) 
            ? (current_suite->stats.passed * 100.0 / current_suite->stats.total) 
            : 0.0;

        printf("| %-15s | %5d | %5d | %5d | %7.0f%% |\n", 
               current_suite->name, 
               current_suite->stats.total, 
               current_suite->stats.passed, 
               current_suite->stats.failed, 
               pass_rate);

        // Update total stats
        total_stats->total += current_suite->stats.total;
        total_stats->passed += current_suite->stats.passed;
        total_stats->failed += current_suite->stats.failed;

        current_suite = current_suite->next;
    }

    // Print total stats
    float total_pass_rate = (total_stats->total > 0) 
        ? (total_stats->passed * 100.0 / total_stats->total) 
        : 0.0;

    printf("+-----------------+-------+-------+-------+----------+\n");
    printf("| %-15s | %5d | %5d | %5d | %7.0f%% |\n", 
           "Total", 
           total_stats->total, 
           total_stats->passed, 
           total_stats->failed, 
           total_pass_rate);
    printf("+-----------------+-------+-------+-------+----------+\n");
    return total_stats;
}
