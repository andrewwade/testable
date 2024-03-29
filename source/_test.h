//
// Created by Andrew Wade on 6/29/18.
//

#ifndef TESTABLE_TEST_H
#define TESTABLE_TEST_H

#include <testable.h>
#include "platform.h"
#include "_node.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Test Control Block
 * @var name        Name of test
 * @var status      Status code of test
 * @var notes       List of notes acquired during test run (if any)
 * @var group       Group containing test (if any)
 * @var function    Pointer to function where test is defined
 */
typedef struct _test_t {
    /* name of the test */
    CHAR *name;

    /* status of the test */
    INT status;

    /* notes acquired during testing (if any) */
    _node_t *callbacks;

    INT callbacks_count;

    /* test function  to run */
    VOID (*function)(struct _test_t *test);

} _test_t;

/**
 * Initialize a test with default values
 * @param test      test control block to initialize
 * @param name      name of test
 * @param function  function pointer to test function
 */
VOID _test_initialize(_test_t *test, CHAR *name, VOID (*function)(_test_t *));

/**
 * Allocate a new test control block
 * @return pointer to new test control block or NULL if out of memory
 */
_test_t *_test_allocate();

/**
 * Release a test control block back to memory
 * @param test pointer to releasing test control block
 */
VOID _test_release(_test_t *test);

/**
 * Add failure callback for when test fails
 * @param test
 * @param callback
 */
VOID _test_add_fail_callback(_test_t *test, VOID *user, fail_callback_t *callback);

/**
 * Remove failure callback
 * @param test
 * @param callback
 */
VOID _test_remove_fail_callback(_test_t *test, VOID *user, fail_callback_t *callback);


/**
 * Run test
 */
VOID _test_run(_test_t *test);

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_TEST_H
