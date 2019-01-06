//
// Created by Andrew Wade on 2019-01-06.
//

#ifndef TESTABLE_MOCK_H
#define TESTABLE_MOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <printf.h>
#include "stdint.h"
#include "_node.h"
#include "_pp.h"


typedef struct _mock_value_t {
    const char *type;
    void       *address;
    size_t     size;
} _mock_value_t;

#define DEFINE_MOCK_VALUE(type) {#type, NULL, sizeof(type)}
#define INIT_MOCK_VALUE(type, var) {#type, &var, sizeof(type)}
#define CREATE_MOCK_VALUE(type, name) _mock_value_t _mock_##name = DEFINE_MOCK_VALUE(type)



typedef struct _mock_variable_t {
    const char   *name;
    _mock_value_t value;
} _mock_variable_t;

#define DEFINE_MOCK_VARIABLE(type, name) { #name, { #type, NULL, sizeof(type)}}
#define INIT_MOCK_VARIABLE(type, var) { #var, INIT_MOCK_VALUE(type, var)}
#define CREATE_MOCK_VARIABLE(type, name) _mock_variable_t _mock_##name = DEFINE_MOCK_VARIABLE(type, name);

typedef struct _mock_call_t {
    _mock_value_t    return_value;
    uint8_t         arguments_count;
    _mock_variable_t arguments[];
} _mock_call_t;


typedef struct _mock_t {
    const char      *name;
    _node_t         *expected;
    _node_t         *actual;
    uint32_t        expected_count;
    uint32_t        actual_count;
    _mock_value_t    return_value;
    uint8_t         arguments_count;
    _mock_variable_t arguments[];
} _mock_t;

#define _MOCK_NAME(name) _mock_##name
#define _MOCK_CALL_BUILDER_TYPE(name) _mock_##name##_call_builder_t
#define _MOCK_CALL_BUILDER_NAME(name) _mock_##name##_call_builder
#define _MOCK_CALL_BUILDER_FUNC(name, func) _mock_##name##_builder_##func

#define _MOCK_CREATE_MOCK(return_type, fname, args...)                                                              \
/* mock definition */                                                                                               \
_mock_t _MOCK_NAME(fname) = {                                                                                       \
    .expected = NULL,                                                                                               \
    .actual = NULL,                                                                                                 \
    .expected_count = 0,                                                                                            \
    .actual_count = 0,                                                                                              \
    .name = #fname,                                                                                                 \
    .return_value = DEFINE_MOCK_VALUE(return_type),                                                                 \
    .arguments_count = COUNT(PAIR_ARGS(args)),                                                                      \
    .arguments = {LIST_FOREACH2(DEFINE_MOCK_VARIABLE, args)},                                                       \
};                                                                                                                  \
                                                                                                                    \
/* function definition */                                                                                           \
return_type fname(PAIR_ARGS(args)) {                                                                                \
    _mock_variable_t with_args[] = {LIST_FOREACH2(INIT_MOCK_VARIABLE, args)};                                       \
    void *return_value_ptr = _mock_call(&_MOCK_NAME(fname), with_args, COUNT(PAIR_ARGS(args)));                     \
    IF(NOT_EQUAL(return_type, void)) (                                                                              \
        /* non void function must return something */                                                               \
        if(return_value_ptr == NULL) {                                                                              \
            /* use default function return value */                                                                 \
            return_value_ptr = _MOCK_NAME(fname).return_value.address;                                              \
        }                                                                                                           \
        /* cast to return type and dereference */                                                                   \
        return *(return_type*)return_value_ptr;                                                                     \
    )                                                                                                               \
}                                                                                                                   \
                                                                                                                    \
/* define call builder */                                                                                           \
typedef struct _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_TYPE(fname);                                       \
struct _MOCK_CALL_BUILDER_TYPE(fname) {                                                                             \
    const _MOCK_CALL_BUILDER_TYPE(fname) (* const TIMES)(int count);                                                \
    const _MOCK_CALL_BUILDER_TYPE(fname) (* const WITH_ARGS)(PAIR_ARGS(args));                                      \
    IF(NOT_EQUAL(return_type, void))(                                                                               \
        const _MOCK_CALL_BUILDER_TYPE(fname) (* const RETURNS)(return_type);                                        \
    )                                                                                                               \
};                                                                                                                  \
                                                                                                                    \
/* declare call builder functions */                                                                                \
static const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname, call_times)(int count);                  \
static const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname,call_with_args)(PAIR_ARGS(args));         \
IF(NOT_EQUAL(void, return_type)) (                                                                                  \
    static const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname,call_returns)(return_type);           \
)                                                                                                                   \
                                                                                                                    \
/* create call builder*/                                                                                            \
const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_NAME(fname) = {                                             \
    _MOCK_CALL_BUILDER_FUNC(fname, call_times),                                                                     \
    _MOCK_CALL_BUILDER_FUNC(fname, call_with_args),                                                                 \
    IF(NOT_EQUAL(void, return_type))(                                                                               \
        _MOCK_CALL_BUILDER_FUNC(fname, call_returns)                                                                \
    )                                                                                                               \
};                                                                                                                  \
                                                                                                                    \
/* define call builder functions */                                                                                 \
const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname, new_call)() {                                   \
    return _MOCK_CALL_BUILDER_NAME(fname);                                                                          \
}                                                                                                                   \
                                                                                                                    \
static const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname, call_times)(int count) {                 \
    _MOCK_NAME(name).expected_count = count;                                                                        \
    return _MOCK_CALL_BUILDER_NAME(fname);                                                                          \
}                                                                                                                   \
                                                                                                                    \
static const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname, call_with_args)(PAIR_ARGS(args)) {       \
    return _MOCK_CALL_BUILDER_NAME(fname);                                                                          \
}                                                                                                                   \
                                                                                                                    \
IF(NOT_EQUAL(void, return_type))(                                                                                   \
    static const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname, call_returns)(return_type value) {   \
        return _mock_##fname##_call_builder;                                                                        \
    }                                                                                                               \
)                                                                                                                   \


void *_mock_call(_mock_t *mock, _mock_variable_t *args, int count);


_MOCK_CREATE_MOCK(int, name, int, a1,int, a2);

#define _MOCK_EXPECT_CALL(func) _mock_##func##_new_call()
#ifdef __cplusplus
};
#endif

#endif //TESTABLE_MOCK_H