//
// Created by Andrew Wade on 6/29/18.
//

#ifndef TESTABLE_GROUPS_H
#define TESTABLE_GROUPS_H

#include "../source/_group.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TEST_GROUP_ACCESS
#define TEST_GROUP_ACCESS(name)                                         \
extern void _group_##name##_initialize()
#endif
#ifndef TEST_GROUP

/** declare a group of tests */
#define TEST_GROUP(name)                                                \
void _group_##name##_initialize(_group_t *group)
#endif /* TEST_GROUP */



#ifndef GROUP_RUN_SINGLE

#define GROUP_RUN_SINGLE(name)                                          \
_group_t _test_group_##name = {                                         \
    #name, /* name of group as string */                                \
    NULL,  /* setup to run before each test */                          \
    NULL,  /* teardown to run after each test */                        \
    NULL,  /* list of tests in group */                                 \
    NULL,  /* list of passed tests */                                   \
    NULL,  /* list of failed tests */                                   \
    NULL,  /* list of skipped tests */                                  \
    0,     /* number of tests in group */                               \
    0,     /* number of passed tests */                                 \
    0,     /* number of failed tests */                                 \
    0      /* number of skipped tests */                                \
};                                                                      \
_group_##name##_initialize(&_test_group_##name);                        \
_group_run_tests(&_test_group_##name)

#endif /* RUN_GROUP */

#define GROUP_CREATE(name)\
_group_t _test_group_##name = {                                         \
        #name, /* name of group as string */                            \
        NULL,  /* setup to run before each test */                      \
        NULL,  /* teardown to run after each test */                    \
        NULL,  /* list of tests in group */                             \
        NULL,  /* list of passed tests */                               \
        NULL,  /* list of failed tests */                               \
        NULL,  /* list of skipped tests */                              \
        0,     /* number of tests in group */                           \
        0,     /* number of passed tests */                             \
        0,     /* number of failed tests */                             \
        0      /* number of skipped tests */                            \
}

#define GROUP_APPEND(name, group) \
_group_##group##_initialize(&_test_group_##name)

#define GROUP_RUN_ALL(name) \
_group_run_tests(&_test_group_##name)

#ifndef TEST_CASE
/** add test case to group */
#define TEST_CASE(name)                                                  \
_test_t *_test_##name = _test_allocate();                               \
_test_initialize(_test_##name, #name, &_test_##name##_function);        \
_group_add_test(group, _test_##name)
#endif /* CASE */


#ifndef TEST_SETUP
/** set test setup for group */
#define TEST_SETUP(name)                                                \
_test_t *_test_setup = _test_allocate();                                \
_test_initialize(_test_setup, "setup "#name, &_test_##name##_function); \
_group_set_setup(group, _test_setup);
#endif /* SETUP */


#ifndef TEST_TEARDOWN
/** set test teardown for group */
#define TEST_TEARDOWN(name)                                                     \
_test_t *_test_teardown = _test_allocate();                                     \
_test_initialize(_test_teardown, "teardown "#name, &_test_##name##_function);   \
_group_set_teardown(group, _test_teardown)
#endif /* TEARDOWN */

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_GROUPABLE_H
