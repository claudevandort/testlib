#include "testlib.h"

int test_verbosity = 1;

typedef struct TestNode {
    void (*test_function)(void);
    const char *test_name;
    struct TestNode *next;
} TestNode;

static TestNode *test_list_head = NULL;

void register_test(const char *test_name, void (*test_function)(void)) {
    TestNode *node = (TestNode *)malloc(sizeof(TestNode));
    if (!node) {
        fprintf(stderr, "Failed to allocate memory for test node.\n");
        exit(EXIT_FAILURE);
    }
    node->test_function = test_function;
    node->test_name = test_name;
    node->next = NULL;

    if (!test_list_head) {
        test_list_head = node;
    } else {
        TestNode *current = test_list_head;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    }
}

void run_tests(void) {
    TestNode *current = test_list_head;
    while (current) {
        if (test_verbosity == 0) {
            current->test_function();
            printf(COLOR_GREEN "." COLOR_RESET);
        } else {
            printf("[RUN ] %s\n", current->test_name);
            current->test_function();
            printf(COLOR_GREEN "[PASS] %s\n\n" COLOR_RESET, current->test_name);
        }
        current = current->next;
    }
    if (test_verbosity == 0) {
        printf("\n");
    }
    current = test_list_head;
    while (current) {
        TestNode *temp = current;
        current = current->next;
        free(temp);
    }
    test_list_head = NULL;
}
