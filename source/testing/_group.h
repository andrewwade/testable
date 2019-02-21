//
// Created by Andrew Wade on 6/29/18.
//

#ifndef TESTABLE_GROUP_H
#define TESTABLE_GROUP_H


#ifdef __cplusplus
extern "C" {
#endif

#include "../utilities/_list.h"

typedef struct _group_t _group_t;
typedef struct _test_t _test_t;

/**
 * Group Control Block
 * @var name            Name of group
 * @var setup           Test setup to be ran before each test
 * @var teardown        Test teardown to be ran after each test
 * @var test            List of all tests in group
 * @var pass            List of all passed tests in group (if any)
 * @var fail            List of all failed tests in group (if any)
 * @var skip            List of all skipped tests in group (if any)
 * @var test_count      Number of tests in group
 * @var pass_count      Number of passed tests in group
 * @var fail_count      Number of failed tests in group
 * @var skip_count      Number of skipped tests in group
 */
struct _group_t {

    /* name of group */
    const char *name;

    /* function to be called before each test in group */
    struct _test_t *setup;

    /* function to be called after each test in group */
    struct _test_t *teardown;

    /* all tests in group */
    _list_t test;

    /* all passed tests in group */
    _list_t pass;

    /* all failed tests in group */
    _list_t fail;

    /* all skipped tests in group */
    _list_t skip;

    /* number of tests in group */
    UINT test_count;

    /* number of passed tests in group */
    UINT pass_count;

    /* number of failed tests in group */
    UINT fail_count;

    /* number of skipped tests in group */
    UINT skip_count;
};

/**
 * Run all tests in group
 * @param group
 */
VOID _group_run_tests(_group_t *group);

/**
 * Set the setup test to be ran before each test case
 * @param group
 * @param test
 */
VOID _group_set_setup(_group_t *group, _test_t *setup);

/**
 * Set the teardown test to be ran after each test case
 * @param group
 * @param test
 */
VOID _group_set_teardown(_group_t *group, _test_t *teardown);

/**
 * Add a test to the group.
 * @param group
 * @param test
 */
VOID _group_add_test(_group_t *group, _test_t *test);

/**
 * Should be called when a test completes with failures
 * @param group
 * @param test
 */
VOID _group_add_fail(_group_t *group, _test_t *test);

/**
 * Should be called when a test completes without failures
 * @param group
 * @param test
 */
VOID _group_add_pass(_group_t *group, _test_t *test);

/**
 * Should be called when a test gets skipped
 * @param group
 * @param test
 */
VOID _group_add_skip(_group_t *group, _test_t *test);

/**
 * Get the setup test to be ran before each test case
 * @param group
 * @return
 */
struct _test_t *_group_get_setup(_group_t *group);

/**
 * Get the teardown test to be ran after each test case
 * @param group
 * @return
 */
struct _test_t *_group_get_teardown(_group_t *group);

/**
 * Get all tests in group
 * @param group
 * @return
 */
struct _node_t *_group_get_all_tests(_group_t *group);

/**
 * Get all tests that passed tests after run
 * @param group
 * @return
 */
struct _node_t *_group_get_passed_tests(_group_t *group);

/**
 * Get all tests that failed tests after run
 * @param group
 * @return
 */
struct _node_t *_group_get_failed_tests(_group_t *group);

/**
 * Get all tests that got skipped during run
 * @param group
 * @return
 */
struct _node_t *_group_get_skipped_tests(_group_t *group);
/**
 * Get number of tests in group
 * @param group
 * @return
 */
UINT _group_get_test_count(_group_t *group);

/**
 * Get number of passed tests in group
 * @param group
 * @return
 */

UINT _group_get_pass_count(_group_t *group);
/**
 * Get number of failed tests in group
 * @param group
 * @return
 */
UINT _group_get_fail_count(_group_t *group);

/**
 * Get number of skipped tests in group
 * @param group
 * @return
 */
UINT _group_get_skip_count(_group_t *group);


#ifdef __cplusplus
};
#endif

#endif //TESTABLE_GROUP_H
