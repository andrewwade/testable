//
// Created by Andrew Wade on 2019-01-06.
//

#ifndef TESTABLE__MOCK_H
#define TESTABLE__MOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <printf.h>
#include "stdint.h"
#include "_node.h"
#include "_pp.h"
#include "_mock_call.h"

#define _MOCK_GET_MOCK(name) _mock_##name
#define _MOCK_GET_MOCK_CALL_BUILDER_TYPE(name) _mock_##name##_call_builder_t
#define _MOCK_GET_MOCK_CALL_BUILDER(name) _mock_##name##_call_builder
#define _MOCK_GET_MOCK_CALL_BUILDER_FUNC(name, func) _mock_##name##_builder_##func

typedef struct _mock_t {
    const char             *name;
    _node_t                *expected_calls;
    _node_t                *received_calls;
    uint32_t               expected_call_count;
    uint32_t               received_call_count;
    const _mock_value_t    return_value;
    const uint8_t          argc;
    const _mock_variable_t argv[];
} _mock_t;


#define _MOCK_CREATE_MOCK(return_type, fname, args...)                                                              \
/* mock definition */                                                                                               \
_mock_t _MOCK_GET_MOCK(fname) = {                                                                                   \
    .name = #fname,                                                                                                 \
    .expected_calls = NULL,                                                                                         \
    .received_calls = NULL,                                                                                         \
    .expected_call_count = 0,                                                                                       \
    .received_call_count = 0,                                                                                       \
    .return_value = _MOCK_VALUE(return_type),                                                                       \
    .argc = IF_ELSE(HAS_ARGS(args))(COUNT(LIST_PAIRS(args)), 0),                                                    \
    .argv = {IF(HAS_ARGS(args))(MAP_PAIRS(_MOCK_VARIABLE, COMMA, args))},                                           \
};                                                                                                                  \
                                                                                                                    \
/* function definition */                                                                                           \
return_type fname(LIST_PAIRS(args)) {                                                                               \
                                                                                                                    \
    IF(HAS_ARGS(args)) (                                                                                            \
        _mock_variable_t with_args[] = {MAP_PAIRS(_MOCK_VARIABLE_FROM_VAR, COMMA, args)};                           \
        void *return_value_ptr = _mock_handle_call(&_MOCK_GET_MOCK(fname), with_args);                              \
        void (*call_callback)(LIST_PAIRS(args)) = _mock_get_last_received_call(&_MOCK_GET_MOCK(fname))->callback;   \
        if(call_callback != NULL) {                                                                                 \
            call_callback(MAP_PAIRS(SECOND, COMMA, args));                                                          \
        }                                                                                                           \
    )                                                                                                               \
    IF(HAS_NO_ARGS(args)) (                                                                                         \
        void *return_value_ptr = _mock_handle_call(&_MOCK_GET_MOCK(fname), NULL);                                   \
        void (*call_callback)(LIST_PAIRS(args)) = _mock_get_last_received_call(&_MOCK_GET_MOCK(fname))->callback;   \
        if(call_callback != NULL) {                                                                                 \
            call_callback();                                                                                        \
        }                                                                                                           \
    )                                                                                                               \
    IF(NOT(TYPE_IS_VOID(return_type))) (                                                                            \
        /* non void function must return something */                                                               \
        if(return_value_ptr == NULL) {                                                                              \
            if(_MOCK_GET_MOCK(fname).return_value.address != NULL) {                                                \
                /* use default function return value */                                                             \
                return_value_ptr = _MOCK_GET_MOCK(fname).return_value.address;                                      \
            } else {                                                                                                \
                printf("Fail: No Return Value\n");                                                                  \
            }                                                                                                       \
        }                                                                                                           \
        /* cast to return type and dereference */                                                                   \
        return *(return_type*)return_value_ptr;                                                                     \
    )                                                                                                               \
}                                                                                                                   \
                                                                                                                    \
/* define call builder */                                                                                           \
typedef struct _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname) _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname);                     \
struct _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname) {                                                                    \
    const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname) (* const CALLBACK)(void (*cb)(LIST_PAIRS(args)));                 \
    const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname) (* const TIMES)(uint32_t count);                                  \
    IF(HAS_ARGS(args)) (                                                                                            \
        const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname) (* const WITH_ARGS)(LIST_PAIRS(args));                        \
    )                                                                                                               \
    IF(NOT(TYPE_IS_VOID(return_type)))(                                                                             \
        const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname) (* const RETURNS)(return_type);                               \
    )                                                                                                               \
};                                                                                                                  \
                                                                                                                    \
/* declare call builder functions */                                                                                \
static const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname)                                                                \
_MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call_callback)(void (*callback)(LIST_PAIRS(args)));                  \
                                                                                                                    \
static const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname)                                                                \
_MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call_times)(uint32_t expected_call_count);                           \
                                                                                                                    \
IF(HAS_ARGS(args)) (                                                                                                \
    static const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname)                                                            \
    _MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname,expect_call_with_args)(LIST_PAIRS(args));                                \
)                                                                                                                   \
                                                                                                                    \
IF(NOT(TYPE_IS_VOID(return_type))) (                                                                                \
    static const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname)                                                            \
    _MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname,expect_call_returns)(return_type);                                       \
)                                                                                                                   \
                                                                                                                    \
/* create call builder*/                                                                                            \
static const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname) _MOCK_GET_MOCK_CALL_BUILDER(fname) = {                         \
    _MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call_callback),                                                  \
    _MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call_times),                                                     \
    IF(HAS_ARGS(args)) (                                                                                            \
        _MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call_with_args),                                             \
    )                                                                                                               \
    IF(NOT(TYPE_IS_VOID(return_type)))(                                                                             \
        _MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call_returns)                                                \
    )                                                                                                               \
};                                                                                                                  \
                                                                                                                    \
/* define call builder functions */                                                                                 \
const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname)                                                                       \
_MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call_callback)(void (*callback)(LIST_PAIRS(args))) {                 \
    _mock_expect_call_callback(&_MOCK_GET_MOCK(fname), callback);                                                   \
    return _MOCK_GET_MOCK_CALL_BUILDER(fname);                                                                      \
}                                                                                                                   \
                                                                                                                    \
const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname)                                                                       \
_MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call)() {                                                            \
    _mock_expect_call(&_MOCK_GET_MOCK(fname));                                                                      \
    return _MOCK_GET_MOCK_CALL_BUILDER(fname);                                                                      \
}                                                                                                                   \
                                                                                                                    \
static const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname)                                                                \
_MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call_times)(uint32_t expected_call_count) {                          \
    _mock_expect_call_times(&_MOCK_GET_MOCK(fname), expected_call_count);                                           \
    return _MOCK_GET_MOCK_CALL_BUILDER(fname);                                                                      \
}                                                                                                                   \
                                                                                                                    \
IF(HAS_ARGS(args)) (                                                                                                \
    static const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname)                                                            \
    _MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call_with_args)(LIST_PAIRS(args)) {                              \
        _mock_variable_t with_args[] = {MAP_PAIRS(_MOCK_VARIABLE_FROM_VAR, COMMA, args)};                           \
        _mock_expect_call_with_args(&_MOCK_GET_MOCK(fname), with_args);                                             \
        return _MOCK_GET_MOCK_CALL_BUILDER(fname);                                                                  \
    }                                                                                                               \
)                                                                                                                   \
                                                                                                                    \
IF(NOT(TYPE_IS_VOID(return_type)))(                                                                                 \
    static const _MOCK_GET_MOCK_CALL_BUILDER_TYPE(fname)                                                            \
    _MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call_returns)(return_type value) {                               \
        _mock_value_t return_value = _MOCK_VALUE_FROM_VAR(return_type, value);                                      \
        _mock_expect_call_returns(&_MOCK_GET_MOCK(fname), return_value);                                            \
        return _mock_##fname##_call_builder;                                                                        \
    }                                                                                                               \
)                                                                                                                   \


#define _MOCK_EXPECT_CALL(fname) _MOCK_GET_MOCK_CALL_BUILDER_FUNC(fname, expect_call)()

void *_mock_handle_call(_mock_t *mock, _mock_variable_t *args);

void _mock_expect_call(_mock_t *mock);

void _mock_expect_call_callback(_mock_t *mock, void *callback);

void _mock_expect_call_with_args(_mock_t *mock, _mock_variable_t *args);

void _mock_expect_call_returns(_mock_t *mock, _mock_value_t return_value);

void _mock_expect_call_times(_mock_t *mock, uint32_t times);

_mock_call_t *_mock_get_last_received_call(_mock_t *mock);

_mock_call_t *_mock_get_last_expected_call(_mock_t *mock);

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_MOCK_H
