//
// Created by Andrew Wade on 2019-01-22.
//

#ifndef TESTABLE_RUNNER_H
#define TESTABLE_RUNNER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "_test.h"
#include "_group.h"

typedef struct _runner_t {
    _group_t group;
//    _output_t output;
} _runner_t;


#ifndef RUN_TEST
#define RUN_TEST(name) do {                                     \
    _test_t _test_##name = {                                    \
        #name,                                                  \
        0,                                                      \
        NULL,                                                   \
        0,                                                      \
        &_test_##name##_function                                \
        };                                                      \
    _test_##name##_function(&_test_##name);                     \
while(0)
#endif


#ifndef RUN_GROUP
#define RUN_GROUP(name) do {                                                \
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
    _group_run_all(&_test_group_##name);                                    \
while(0)

#endif /* RUN_GROUP */

#define CREATE_RUNNER(name)                                             \
_runner_t _test_runner_##name = {                                       \
    {                                                                   \
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
    }                                                                   \
}

#define RUNNER_ADD_GROUP(runner_name, group_name)                   \
_group_##group_name##_initialize(&_test_runner_##runner_name.group)

#define RUNNER_ADD_TEST(runner, test) \
_test_t *_test_##test = _test_allocate();                               \
_test_initialize(_test_##test, #test, &_test_##test##_function);        \
_group_add_test(&_test_runner_##runner.group, _test_##test)             \

#define RUNNER_RUN(runner_name)\
_group_run_tests(&_test_runner_##runner_name.group)

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_RUNNER_H
