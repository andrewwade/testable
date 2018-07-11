//
// Created by Andrew Wade on 7/1/18.
//

#include "testing.h"
#include "../source/_node.h"
#include <setjmp.h>
#include <printf.h>

jmp_buf temp_jump;

void copy_jmp(jmp_buf dest, jmp_buf src) {
    for(int i = 0; i < _JBLEN; i++) {
        dest[i] = src[i];
    }
}

int asserts_failed = 0;
int assert_fail_count = 0;
void assert_failure(int code, char *message) {
    printf("%s", message);
    fflush(stdout);
    asserts_failed++;
}

void assert_failure_expected(void *user, int code, char *message) {
    asserts_failed++;
}
fail_callback_t expect_assert_fail = {NULL, assert_failure_expected};

#define EXPECT_ASSERT_FAIL(call, message...)              \
expect_assert_fail.user = test;                           \
_assert_add_fail_callback(&expect_assert_fail);           \
_assert_push_fail_point(&temp_jump);                      \
if(!setjmp(temp_jump)) {                                  \
    assert_fail_count = asserts_failed;                   \
    call;                                                 \
}                                                         \
_assert_pop_fail_point();                                 \
_assert_remove_fail_callback(&expect_assert_fail);        \
ASSERT_INT_EQ(assert_fail_count+1,asserts_failed, message)

TEST(_node_initialize_check_for_null_node) {
    EXPECT_ASSERT_FAIL(_node_initialize(NULL, NULL), "_node_initialize did not check for NULL");
}

TEST(_node_initialize_allow_null_data) {
    _node_t node;
    _node_initialize(&node, NULL);
}

TEST(_node_initialize_set_next_to_node) {
    _node_t node;
    _node_initialize(&node, NULL);

    ASSERT_PTR_EQ(&node, node.next);
}

TEST(_node_initialize_set_previous_to_node) {
    _node_t node;
    _node_initialize(&node, NULL);

    ASSERT_PTR_EQ(&node, node.prev);
}

TEST(_node_initialize_set_data_to_data_arg) {
    _node_t node;
    int data;

    _node_initialize(&node, &data);

    ASSERT_PTR_EQ(&data, node.data);
}

TEST(_node_remove_check_for_null_node) {
    _node_remove(NULL);
}

TEST(_node_remove_links_previous_to_next) {
    _node_t node, next, previous;

    node.next     = &next;
    node.prev = &previous;
    _node_remove(&node);

    ASSERT_PTR_EQ(&next, previous.next);
}

TEST(_node_remove_links_next_to_previous) {
    _node_t node, next, previous;

    node.next     = &next;
    node.prev = &previous;
    _node_remove(&node);

    ASSERT_PTR_EQ(&previous, next.prev);
}

TEST(_node_insert_check_for_null_nodes) {
    _node_t node;
    EXPECT_ASSERT_FAIL(_node_insert(NULL,&node));
    EXPECT_ASSERT_FAIL(_node_insert(&node, NULL));
}

TEST_GROUP(node_test) {
    TEST_CASE(_node_initialize_allow_null_data);
    TEST_CASE(_node_initialize_check_for_null_node);
    TEST_CASE(_node_initialize_set_next_to_node);
    TEST_CASE(_node_initialize_set_previous_to_node);
    TEST_CASE(_node_initialize_set_data_to_data_arg);
    TEST_CASE(_node_remove_check_for_null_node);
    TEST_CASE(_node_insert_check_for_null_nodes);
}
