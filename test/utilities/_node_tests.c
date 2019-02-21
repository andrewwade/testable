//
// Created by Andrew Wade on 7/1/18.
//

#include "clarity/testing.h"
#include "../../source/utilities/_list.h"
#include <setjmp.h>
#include <printf.h>


TEST(_node_initialize_check_for_null_node) {

    EXPECT_ASSERT_FAILURE(_node_initialize(NULL, NULL), "_node_initialize() did not check for NULL");
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

TEST_GROUP(node_tests) {
    TEST_CASE(_node_initialize_allow_null_data);
    TEST_CASE(_node_initialize_check_for_null_node);
    TEST_CASE(_node_initialize_set_next_to_node);
    TEST_CASE(_node_initialize_set_previous_to_node);
    TEST_CASE(_node_initialize_set_data_to_data_arg);
}