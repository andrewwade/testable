//
// Created by Andrew Wade on 7/2/18.
//
#include <stdlib.h>
#include "_node.h"
#include "_test.h"
#include "_pool.h"
#include "assertable.h"

#ifndef TEST_POOL_SIZE
#define TEST_POOL_SIZE 512
#endif

static _test_t pool_buffer[TEST_POOL_SIZE];
static pool_t pool = {0};

void _test_pool_initialize() {
    pool_init(&pool, pool_buffer, TEST_POOL_SIZE*sizeof(_test_t), sizeof(_test_t));
}

VOID _test_initialize(_test_t *test, CHAR *name, VOID (*function)(_test_t *)) {
    test->name = name;
    test->status = 0;
    test->notes = NULL;

    test->function = function;
}

_test_t *_test_allocate() {
    if (pool.memory != pool_buffer) {
        _test_pool_initialize();
    }
    return pool_alloc(&pool);
}

VOID _test_release(_test_t *test) {
    ASSERT_EQ(0, pool_free(&pool, test));
}
