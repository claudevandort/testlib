#include "testlib.h"

static TestNode* test_list_head = NULL;
TestNode* current_test = NULL;

int test_verbosity = 1;

void register_test(const char *test_name, void (*test_function)(void)) {
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

    if (!test_list_head) {
        test_list_head = new_test;
    } else {
        TestNode* current = test_list_head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_test;
    }
}

TestStats run_tests(void) {
    TestStats stats = {0, 0, 0};
    TestNode* current = test_list_head;

    while (current) {
        current_test = current;
        current_test->function();

        stats.total++;
        if (current_test->passed) {
            stats.passed++;
            if (test_verbosity == 0) {
                printf(COLOR_GREEN "." COLOR_RESET);
                fflush(stdout);
            } else if (test_verbosity > 0) {
                printf(COLOR_GREEN "[PASS]" COLOR_RESET " %s\n", current_test->name);
            }
        } else {
            stats.failed++;
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

        if (current_test->failure_message) {
            free(current_test->failure_message);
            current_test->failure_message = NULL;
        }

        current = current->next;
    }

    if (test_verbosity == 0) {
        printf("\n");
    }

    current = test_list_head;
    while (current) {
        TestNode* temp = current;
        current = current->next;
        free(temp);
    }
    test_list_head = NULL;

    print_test_report(&stats);

    return stats;
}

void print_test_report(const TestStats* stats) {
    printf("\nTest results: %d total, %d passed, %d failed\n", stats->total, stats->passed, stats->failed);
}
