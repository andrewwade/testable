//
// Created by Andrew Wade on 7/2/18.
//
#include <stdlib.h>
#include <printf.h>
#include "../utilities/_list.h"
#include "../utilities/_pool.h"
#include "_test.h"
#include <clarity/testing.h>

#ifndef TEST_POOL_SIZE
#define TEST_POOL_SIZE 512
#endif

static _test_t test_pool_buffer[TEST_POOL_SIZE];
static _pool_t test_pool = {0};


static VOID test_assert_fail_callback(void *user, int code, char *message) {
    _test_t         *test = user;
    _node_t         *node = test->fail_callbacks.elements;
    fail_callback_t *callback;

    for (int i = 0; i < test->fail_callbacks.size; i++) {
        callback = _node_data(node);
        callback->call(callback->user, code, message);
        node = _node_next(node);
    }

    TEST_OUTPUT("%s", message);
}


void _test_pool_initialize() {
    _pool_init(&test_pool, sizeof(_test_t), test_pool_buffer, &test_pool_buffer[TEST_POOL_SIZE]);
}

VOID _test_initialize(_test_t *self, CHAR *name, VOID (*run)(_test_t *)) {
    self->name = name;
    self->run  = run;
    _list_init(&self->fail_callbacks, self);
}

_test_t *_test_allocate() {
    if (!_pool_is_valid(&test_pool)) {
        _test_pool_initialize();
    }
    return _pool_allocate(&test_pool);
}

VOID _test_release(_test_t *self) {
    _pool_release(&test_pool, self);
}


VOID _test_add_fail_callback(_test_t *self, void *user, fail_callback_t *callback) {
    _node_t *node;

    ASSERT_PTR_NE(NULL, self);
    ASSERT_PTR_NE(NULL, callback);

    _list_append(&self->fail_callbacks, callback);
}

VOID _test_remove_fail_callback(_test_t *test, VOID *user, fail_callback_t *callback) {

    ASSERT_PTR_NE(NULL, test);
    ASSERT_PTR_NE(NULL, callback);
    _list_remove(&test->fail_callbacks, callback);
}

VOID _test_run(_test_t *test) {
    fail_callback_t test_fail_callback = {test, test_assert_fail_callback};
    /* add test_callback to assert callbacks so new test callback can be called */
    _assert_add_fail_callback(&test_fail_callback);
    test->run(test);
    _assert_remove_fail_callback(&test_fail_callback);
}