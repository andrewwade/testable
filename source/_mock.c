//
// Created by Andrew Wade on 12/8/18.
//
#include <printf.h>
#include "stdint.h"
#include "_node.h"
#include "_pp.h"

#define MOCK_IGNORE_UNEXPECTED 0x01

#define DEFINE_VALUE(type) {#type, NULL, sizeof(type)}
#define INIT_VALUE(type, var) {#type, &var, sizeof(type)}

typedef struct _value_t {
    const char *type;
    void       *address;
    size_t     size;
} _value_t;

#define DEFINE_VARIABLE(type, var) { #var, { #type, NULL, sizeof(type)}}
#define INIT_VARIABLE(type, var) { #var, INIT_VALUE(type, var)}

typedef struct _variable_t {
    const char *name;
    _value_t   value;
} _variable_t;

typedef struct _funcion_t {
    const char  *name;
    _value_t    return_value;
    uint8_t     arguments_count;
    _variable_t arguments[];
} _function_t;


typedef struct _mock_t {
    const char  *name;
    _node_t     *expected;
    _node_t     *actual;
    uint32_t    expected_count;
    uint32_t    actual_count;
    _value_t    return_value;
    uint8_t     arguments_count;
    _variable_t arguments[];
} _mock_t;


void *mock_call(_mock_t *mock, _variable_t *args, int count) {
    printf("%s %s(", mock->return_value.type, mock->name);
    for (int i = 0; i < mock->arguments_count; i++) {
        _variable_t *arg = &mock->arguments[i];
        printf("%s %s,", arg->value.type, arg->name);
    }
    printf("):\n");
    if (mock->expected_count > mock->actual_count) {
        // handle expected call


        // return expected return value
    } else {
        // handle unexpected calls

        // create memory zeroized memory block to return

    }
    return NULL;
}

#define _MOCK_NAME(name) _mock_##name

#define _MOCK_FUN(name) _mock_func_##name


#define _MOCK_CREATE_MOCK_T(return_type, fname, args...)                                                \
/* mock definition */                                                                                   \
_mock_t _mock_##fname = {                                                                               \
    .expected = NULL,                                                                                   \
    .actual = NULL,                                                                                     \
    .expected_count = 0,                                                                                \
    .actual_count = 0,                                                                                  \
    .name = #fname,                                                                                     \
    .return_value = DEFINE_VALUE(return_type),                                                          \
    .arguments_count = COUNT(PAIR_ARGS(args)),                                                          \
    .arguments = {LIST_FOREACH2(DEFINE_VARIABLE, args)},                                                \
}

#define _MOCK_DEFINE_FUNCTION(return_type, fname, args...)                                              \
/* function definition */                                                                               \
return_type fname(PAIR_ARGS(args)) {                                                                    \
    _variable_t with_args[] = {LIST_FOREACH2(INIT_VARIABLE, args)};                                     \
    void *return_value_ptr = mock_call(&_mock_##fname, with_args, COUNT(PAIR_ARGS(args)));              \
    IF(NOT_EQUAL(return_type, void)) (                                                                  \
        /* non void function must return something */                                                   \
        if(return_value_ptr == NULL) {                                                                  \
            /* use default function return value */                                                     \
            return_value_ptr = _mock_##fname.return_value.address;                                      \
        }                                                                                               \
        /* cast to return type and dereference */                                                       \
        return *(return_type*)return_value_ptr;                                                         \
    )                                                                                                   \
}

#define _MOCK_CREATE_CALL_BUILDER_T(return_type, fname, args...)                                        \
/* define call builder */                                                                               \
typedef struct _mock_##fname##_call_builder_t _mock_##fname##_call_builder_t;                           \
struct _mock_##fname##_call_builder_t {                                                                 \
    const _mock_##fname##_call_builder_t (* const TIMES)(int count);                                    \
    const _mock_##fname##_call_builder_t (* const WITH_ARGS)(PAIR_ARGS(args));                          \
    IF(NOT_EQUAL(return_type, void))(                                                                   \
        const _mock_##fname##_call_builder_t (* const RETURNS)(return_type);                            \
    )                                                                                                   \
};                                                                                                      \
/* declare call builder functions */                                                                    \
static const _mock_##fname##_call_builder_t _mock_##fname##_call_times(int count);                      \
static const _mock_##fname##_call_builder_t _mock_##fname##_call_with_args(PAIR_ARGS(args));            \
static const _mock_##fname##_call_builder_t _mock_##fname##_call_returns(return_type);                  \
/* create call builder*/                                                                                \
const _mock_##fname##_call_builder_t _mock_##fname##_call_builder = {                                   \
    _mock_##fname##_call_times,                                                                         \
    _mock_##fname##_call_with_args,                                                                     \
    IF(NOT_EQUAL(void, return_type))(                                                                   \
        _mock_##fname##_call_returns                                                                    \
    )                                                                                                   \
}

#define _MOCK_DEFINE_CALL_BUILDER_FUNCTIONS(return_type, fname, args...)                                \
/* define call builder functions */                                                                     \
const _mock_##fname##_call_builder_t _mock_##fname##_new_call() {                                       \
    return _mock_##fname##_call_builder;                                                                \
}                                                                                                       \
                                                                                                        \
static const _mock_##fname##_call_builder_t _mock_##fname##_call_times(int count) {                     \
    _mock_##fname.expected_count = count;                                                               \
    return _mock_##fname##_call_builder;                                                                \
}                                                                                                       \
                                                                                                        \
static const _mock_##fname##_call_builder_t _mock_##fname##_call_with_args(PAIR_ARGS(args)) {           \
    return _mock_##fname##_call_builder;                                                                \
}                                                                                                       \
                                                                                                        \
IF(NOT_EQUAL(void, return_type))(                                                                       \
    static const _mock_##fname##_call_builder_t _mock_##fname##_call_returns(return_type value) {       \
        return _mock_##fname##_call_builder;                                                            \
    }                                                                                                   \
)\

#define MOCK(return_type, fname, args...)                                                               \
                                                                                                        \
_MOCK_CREATE_MOCK_T(return_type, fname, args);                                                          \
                                                                                                        \
_MOCK_DEFINE_FUNCTION(return_type, fname, args);                                                        \
                                                                                                        \
_MOCK_CREATE_CALL_BUILDER_T(return_type, fname, args);                                                  \
                                                                                                        \
_MOCK_DEFINE_CALL_BUILDER_FUNCTIONS(return_type, fname,args)

#define _FILL_VAR_ARGS(vtype, vname) {.name = #vname, .value.address = &(vname), .value.type = #vtype, .value.size=sizeof(vtype)}

#define EXPECT_CALL(func) _mock_##func##_new_call()


MOCK(int, test_function, int, a1, int, a2);
MOCK(void, test_void_function, char*, s);


void my_test() {
    EXPECT_CALL(test_function).WITH_ARGS(3, 2).RETURNS(3);
    EXPECT_CALL(test_function).WITH_ARGS(3, 2).TIMES(3);

    test_function(1, 2);
}

int main() {
    my_test();
}