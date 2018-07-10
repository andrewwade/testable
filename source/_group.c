//
// Created by Andrew Wade on 6/29/18.
//

#include "../include/assertable.h"
#include "_node.h"
#include "_test.h"
#include "_group.h"
#include <stdio.h>
#include <setjmp.h>

jmp_buf test_jump = {0};

void _group_run_all(_group_t *group) {
    _test_t *setup, *teardown, *test;
    _node_t *head, *node;

    ASSERT_PTR_NE(NULL, group, "No group to run.");

    setup    = group->setup;
    teardown = group->teardown;
    head     = group->test;
    node     = head;

    ASSERT_PTR_NE(head, NULL, "No tests to run in group %s.", group->name);

    /* run all tests */
    do {
        if (node == NULL) {
            printf("Error: Test is NULL!\n");
            break;
        }

        test = node->data;

        if (!setjmp(test_jump)) {
            printf("Running Test[%s]:\n", test->name);
            /* check if setup exists */
            if (setup) {
                /* run setup */
                setup->function(setup);
            }

            /* run test function */
            test->function(test);

            /* check if teardown exists */
            if (teardown) {
                /* run teardown function */
                teardown->function(teardown);
            }
            printf("  --Done\n");

        } else {
            printf("Test %s failed.\n", test->name);
            return;
        }

        /* move to next test */
        node = node->next;
    } while (node != head);
}

void _group_set_setup(_group_t *group, _test_t *test) {
    group->setup = test;
}

void _group_set_teardown(_group_t *group, _test_t *test) {
    group->teardown = test;
}

void _group_add_test(_group_t *group, _test_t *test) {
    _node_t *new_node;

    ASSERT_PTR_NE(group, NULL);
    ASSERT_PTR_NE(test, NULL);
    ASSERT_PTR_NE(new_node = _node_allocate(), NULL);

    /* set node data to test */
    _node_initialize(new_node, test);

    /* check if group is empty */
    if (group->test == NULL) {
        /* add first test into group */
        group->test = new_node;
    } else {
        /* add test to group */
        _node_insert(group->test, new_node);
    }
}

void _group_add_fail(_group_t *group, _test_t *test) {
    _node_t *new_node;

    ASSERT_PTR_NE(NULL, group);
    ASSERT_PTR_NE(NULL, test);

    /* get new node */
    ASSERT_PTR_NE(NULL, new_node = _node_allocate());

    /* initialize new node with test */
    _node_initialize(new_node, test);

    /* check if fail list is empty */
    if(group->fail == NULL) {
        /* insert new node into fail list as first node */
        group->fail = new_node;
    } else {
        /* insert new node into fail list */
        _node_insert(group->fail, new_node);
    }

    /* increase number of failed tests */
    group->fail_count++;
}

void _group_add_pass(_group_t *group, _test_t *test) {
    _node_t *new_node;
    
    ASSERT_PTR_NE(NULL, group);
    ASSERT_PTR_NE(NULL, test);
    
    /* get new node */
    ASSERT_PTR_NE(NULL, new_node = _node_allocate());
    
    /* initialize new node with test */
    _node_initialize(new_node, test);
    
    /* check if pass list is empty */
    if(group->pass == NULL) {
        /* insert new node into pass list as first node */
        group->pass = new_node;
    } else {
        /* insert new node into pass list */
        _node_insert(group->pass, new_node);
    }
    
    /* increase number of passed tests */
    group->pass_count++;
}

void _group_add_skip(_group_t *group, _test_t *test) {
    _node_t *new_node;

    ASSERT_PTR_NE(NULL, group);
    ASSERT_PTR_NE(NULL, test);

    /* get new node */
    ASSERT_PTR_NE(NULL, new_node = _node_allocate());

    /* initialize new node with test */
    _node_initialize(new_node, test);

    /* check if skip list is empty */
    if(group->skip == NULL) {
        /* insert new node into skip list as first node */
        group->skip = new_node;
    } else {
        /* insert new node into skip list */
        _node_insert(group->skip, new_node);
    }

    /* increase number of skipped tests */
    group->skip_count++;
}

_test_t *_group_get_setup(_group_t *group) {
    ASSERT_PTR_NE(NULL, group);
    return group->setup;
}

_test_t *_group_get_teardown(_group_t *group) {
    ASSERT_PTR_NE(NULL, group);
    return group->teardown;
}

_node_t *_group_get_all_tests(_group_t *group) {
    ASSERT_PTR_NE(NULL, group);
    return group->test;
}

_node_t *_group_get_passed_tests(_group_t *group) {
    ASSERT_PTR_NE(NULL, group);
    return group->pass;
}

_node_t *_group_get_failed_tests(_group_t *group) {
    ASSERT_PTR_NE(NULL, group);
    return group->fail;
}

_node_t *_group_get_skipped_tests(_group_t *group) {
    ASSERT_PTR_NE(NULL, group);
    return group->skip;
}

UINT _group_get_test_count(_group_t *group) {
    ASSERT_PTR_NE(NULL, group);
    return group->test_count;
}

UINT _group_get_pass_count(_group_t *group) {
    ASSERT_PTR_NE(NULL, group);
    return group->pass_count;
}

UINT _group_get_fail_count(_group_t *group) {
    ASSERT_PTR_NE(NULL, group);
    return group->fail_count;
}

UINT _group_get_skip_count(_group_t *group) {
    ASSERT_PTR_NE(NULL, group);
    return group->skip_count;
}