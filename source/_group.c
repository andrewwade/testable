//
// Created by Andrew Wade on 6/29/18.
//

#include "asserts.h"
#include "_list.h"
#include "_test.h"
#include "_group.h"
#include <stdio.h>

#define OUTPUT_RESULT_ALIGNMENT 64

static void group_test_fail_callback(void *user, int code, char *message) {
    _group_t *group = user;
    TEST_OUTPUT("Fail(%d)\n", code);
}

void _group_run_tests(_group_t *group) {
    int count = 0;
    _test_t *setup, *teardown, *test;
    _node_t *head, *node;
    jmp_buf group_fail_point = {0};

    ASSERT_PTR_NE(NULL, group, "No group to run.");

    setup    = group->setup;
    teardown = group->teardown;
    head     = group->test;
    node     = head;

    ASSERT_PTR_NE(head, NULL, "No tests to run in group %s.", group->name);

    /* add group fail point so assertions can fail properly */
    _assert_push_fail_point(&group_fail_point);


    /* run all tests */
    do {
        if (node == NULL) {
            TEST_OUTPUT("Error: Test is NULL!\n");
            break;
        }

        test = node->data;

        /* add fail callback so output can print properly */
        fail_callback_t group_fail_callback = {group, group_test_fail_callback};
        _test_add_fail_callback(test, group, &group_fail_callback);

        /* set group fail point using jump */
        if (!setjmp(group_fail_point)) {
            count = TEST_OUTPUT("Running Test: %s...", test->name);
            while(count < OUTPUT_RESULT_ALIGNMENT) {
                TEST_OUTPUT(".");
                count++;
            }

            /* check if setup exists */
            if (setup) {
                /* run setup */
                setup->function(setup);
            }

            /* run test function */
            _test_run(test);

            /* check if teardown exists */
            if (teardown) {
                /* run teardown function */
                teardown->function(teardown);
            }
            _group_add_pass(group, test);

            TEST_OUTPUT("Pass\n");

        } else {
            _group_add_fail(group, test);
        }
        /* remove test fail callback */
        _test_remove_fail_callback(test, group, &group_fail_callback);

        /* move to next test */
        node = node->next;
    } while (node != head);


    /* remove group fail point */
    _assert_pop_fail_point();

    TEST_OUTPUT("\nTest group '%s' passed %d out of %d.\n\n", group->name, group->pass_count, group->test_count);
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
        _list_insert(group->test, new_node);
    }
    group->test_count++;
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
        _list_insert(group->fail, new_node);
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
        _list_insert(group->pass, new_node);
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
        _list_insert(group->skip, new_node);
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