//
// Created by Andrew Wade on 2019-01-22.
//

#include "_list_tests.h"
//
// Created by Andrew Wade on 7/1/18.
//

#include "clarity/testing.h"
#include "../../source/utilities/_list.h"
#include <setjmp.h>
#include <printf.h>


TEST(_list_remove_check_for_null_node) {
    _list_remove(NULL, NULL);
}

TEST(_list_remove_links_previous_to_next) {
    _list_t list;
    _node_t node, next, previous;

    node.next = &next;
    node.prev = &previous;
    list.elements = &node;
    list.size = 1;
    _list_remove(&list, &node);

    ASSERT_PTR_EQ(&next, previous.next);
}

TEST(_list_remove_links_next_to_previous) {
    _list_t list;
    _node_t node, next, previous;

    node.next     = &next;
    node.prev = &previous;
    _list_remove(&list, &node);

    ASSERT_PTR_EQ(&previous, next.prev);
}

TEST(_list_insert_check_for_null_nodes) {
    _node_t node;
    EXPECT_ASSERT_FAILURE(_list_insert(NULL, 0, &node));
    EXPECT_ASSERT_FAILURE(_list_insert(&node, 0, NULL));
}

TEST_GROUP(list_tests) {
    TEST_CASE(_list_remove_links_previous_to_next);
    TEST_CASE(_list_remove_links_next_to_previous);
    TEST_CASE(_list_remove_check_for_null_node);
    TEST_CASE(_list_insert_check_for_null_nodes);
}
