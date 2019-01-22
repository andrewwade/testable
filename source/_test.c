//
// Created by Andrew Wade on 7/2/18.
//
#include <stdlib.h>
#include <printf.h>
#include "_list.h"
#include "_test.h"
#include "_pool.h"

#ifndef TEST_POOL_SIZE
#define TEST_POOL_SIZE 512
#endif

static _test_t test_pool_buffer[TEST_POOL_SIZE];
static _pool_t  test_pool = {0};


static VOID test_assert_fail_callback(void *user, int code, char *message) {
    _test_t         *test = user;
    _node_t         *node = test->callbacks;
    fail_callback_t *callback;

    for (int i = 0; i < test->callbacks_count; i++) {
        callback = _node_data(node);
        callback->call(callback->user, code, message);
        node = _node_next(node);
    }

    TEST_OUTPUT("%s", message);
}


void _test_pool_initialize() {
    _pool_init(&test_pool, sizeof(_test_t), test_pool_buffer, &test_pool_buffer[TEST_POOL_SIZE]);
}

VOID _test_initialize(_test_t *test, CHAR *name, VOID (*function)(_test_t *)) {
    test->name      = name;
    test->status    = 0;
    test->callbacks = NULL;
    test->function  = function;
}

_test_t *_test_allocate() {
    if (!_pool_is_valid(&test_pool)) {
        _test_pool_initialize();
    }
    return _pool_allocate(&test_pool);
}

VOID _test_release(_test_t *test) {
    _pool_release(&test_pool, test);
}


VOID _test_add_fail_callback(_test_t *test, void *user, fail_callback_t *callback) {
    _node_t *node;

    ASSERT_PTR_NE(NULL, test);
    ASSERT_PTR_NE(NULL, callback);

    /* setup new node */
    node = _node_allocate();
    _node_initialize(node, callback);

    /* check if fail callbacks is empty */
    if (test->callbacks == NULL) {
        /* insert first node in fail callbacks list */
        test->callbacks = node;
    } else {
        /* insert new callback into faile callbacks list */
        _list_insert(test->callbacks, node);
    }
    test->callbacks_count++;
}

VOID _test_remove_fail_callback(_test_t *test, VOID *user, fail_callback_t *callback) {
    _node_t *node;

    ASSERT_PTR_NE(NULL, test);
    ASSERT_PTR_NE(NULL, callback);

    /* check if there are any callbacks */
    if (test->callbacks != NULL) {
        /* iterate to find removal node */
        node = test->callbacks;
        do {
            if (_node_data(node) == callback) {
                /* remove node */
                _list_remove(node);
                _node_release(node);
                test->callbacks_count--;
                break;
            }
            node = _node_next(node);
        } while (node != test->callbacks);
        if (test->callbacks_count == 0) {
            test->callbacks = NULL;
        }
    }
}

VOID _test_run(_test_t *test) {
    fail_callback_t test_fail_callback = {test, test_assert_fail_callback};
    /* add test_callback to assert callbacks so new test callback can be called */
    _assert_add_fail_callback(&test_fail_callback);
    test->function(test);
    _assert_remove_fail_callback(&test_fail_callback);
}