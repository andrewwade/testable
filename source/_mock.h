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
    void *          override_function;
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
#define _MOCK_CALL_BUILDER(name) _mock_##name##_call_builder
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
    .arguments_count = COUNT(LIST_PAIRS(args)),                                                                     \
    .arguments = {MAP_PAIRS(DEFINE_MOCK_VARIABLE, COMMA, args)},                                                    \
};                                                                                                                  \
                                                                                                                    \
/* function definition */                                                                                           \
return_type fname(LIST_PAIRS(args)) {                                                                               \
    _mock_variable_t with_args[] = {MAP_PAIRS(INIT_MOCK_VARIABLE, COMMA, args)};                                    \
    void *return_value_ptr = _mock_call(&_MOCK_NAME(fname), with_args, COUNT(LIST_PAIRS(args)));                    \
    IF(NOT(TYPE_IS_VOID(return_type))) (                                                                            \
        /* non void function must return something */                                                               \
        if(return_value_ptr == NULL && _MOCK_NAME(fname).return_value.address != NULL) {                            \
            /* use default function return value */                                                                 \
            return_value_ptr = _MOCK_NAME(fname).return_value.address;                                              \
        } else {                                                                                                    \
            printf("Fail: No Return Value\n");                                                                      \
        }                                                                                                           \
        /* cast to return type and dereference */                                                                   \
        return *(return_type*)return_value_ptr;                                                                     \
    )                                                                                                               \
}                                                                                                                   \
                                                                                                                    \
/* define call builder */                                                                                           \
typedef struct _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_TYPE(fname);                                       \
struct _MOCK_CALL_BUILDER_TYPE(fname) {                                                                             \
    const _MOCK_CALL_BUILDER_TYPE(fname) (* const OVERRIDE)(return_type (*override)(LIST_PAIRS(args)));             \
    const _MOCK_CALL_BUILDER_TYPE(fname) (* const TIMES)(int count);                                                \
    const _MOCK_CALL_BUILDER_TYPE(fname) (* const WITH_ARGS)(LIST_PAIRS(args));                                     \
    IF(NOT(TYPE_IS_VOID(return_type)))(                                                                             \
        const _MOCK_CALL_BUILDER_TYPE(fname) (* const RETURNS)(return_type);                                        \
    )                                                                                                               \
};                                                                                                                  \
                                                                                                                    \
/* declare call builder functions */                                                                                \
static const _MOCK_CALL_BUILDER_TYPE(fname)                                                                         \
_MOCK_CALL_BUILDER_FUNC(fname, set_override)(return_type (*callback)(LIST_PAIRS(args)));                            \
                                                                                                                    \
static const _MOCK_CALL_BUILDER_TYPE(fname)                                                                         \
_MOCK_CALL_BUILDER_FUNC(fname, call_times)(int count);                                                              \
                                                                                                                    \
static const _MOCK_CALL_BUILDER_TYPE(fname)                                                                         \
_MOCK_CALL_BUILDER_FUNC(fname,call_with_args)(LIST_PAIRS(args));                                                    \
                                                                                                                    \
IF(NOT(TYPE_IS_VOID(return_type))) (                                                                                \
    static const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname,call_returns)(return_type);           \
)                                                                                                                   \
                                                                                                                    \
/* create call builder*/                                                                                            \
static const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER(fname) = {                                           \
    _MOCK_CALL_BUILDER_FUNC(fname, set_override),                                                                   \
    _MOCK_CALL_BUILDER_FUNC(fname, call_times),                                                                     \
    _MOCK_CALL_BUILDER_FUNC(fname, call_with_args),                                                                 \
    IF(NOT(TYPE_IS_VOID(return_type)))(                                                                             \
        _MOCK_CALL_BUILDER_FUNC(fname, call_returns)                                                                \
    )                                                                                                               \
};                                                                                                                  \
                                                                                                                    \
/* define call builder functions */                                                                                 \
const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname, set_override)() {                               \
    return _MOCK_CALL_BUILDER(fname);                                                                               \
}                                                                                                                   \
                                                                                                                    \
const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname, new_call)() {                                   \
    return _MOCK_CALL_BUILDER(fname);                                                                               \
}                                                                                                                   \
                                                                                                                    \
static const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname, call_times)(int count) {                 \
    _MOCK_NAME(fname).expected_count = count;                                                                       \
    return _MOCK_CALL_BUILDER(fname);                                                                               \
}                                                                                                                   \
                                                                                                                    \
static const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname, call_with_args)(LIST_PAIRS(args)) {      \
    return _MOCK_CALL_BUILDER(fname);                                                                               \
}                                                                                                                   \
                                                                                                                    \
IF(NOT(TYPE_IS_VOID(return_type)))(                                                                                 \
    static const _MOCK_CALL_BUILDER_TYPE(fname) _MOCK_CALL_BUILDER_FUNC(fname, call_returns)(return_type value) {   \
        return _mock_##fname##_call_builder;                                                                        \
    }                                                                                                               \
)                                                                                                                   \


void *_mock_call(_mock_t *mock, _mock_variable_t *args, int count);



#define _MOCK_EXPECT_CALL(fname) _MOCK_CALL_BUILDER_FUNC(fname, new_call)()

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_MOCK_H
