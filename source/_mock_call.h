//
// Created by Andrew Wade on 2019-01-10.
//

#ifndef TESTABLE_MOCK_CALL_H
#define TESTABLE_MOCK_CALL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "_node.h"

typedef struct _mock_value_t {
    const char *type;
    void       *address;
    size_t     size;
} _mock_value_t;

#define _MOCK_VALUE(type) {#type, NULL, sizeof(type)}
#define _MOCK_VALUE_FROM_VAR(type, var) {#type, &var, sizeof(type)}


typedef struct _mock_variable_t {
    const char    *name;
    _mock_value_t value;
} _mock_variable_t;

#define _MOCK_VARIABLE(type, name) { #name, { #type, NULL, sizeof(type)}}
#define _MOCK_VARIABLE_FROM_VAR(type, var) { #var, _MOCK_VALUE_FROM_VAR(type, var)}

typedef struct _mock_call_t {
    void *callback;
    uint32_t         call_count;
    _mock_value_t    return_value;
    uint8_t          argc;
    _mock_variable_t *argv;
} _mock_call_t;


_mock_call_t * _mock_call_create(_mock_value_t returns, _mock_variable_t *argv, uint8_t argc);

void _mock_call_destroy(_mock_call_t * call);

void _mock_call_set_call_count(_mock_call_t *call, uint32_t count);

void _mock_call_increment_call_count(_mock_call_t *call);

void _mock_call_decrement_call_count(_mock_call_t *call);

void _mock_call_set_return_value(_mock_call_t *call, _mock_value_t value);

void _mock_call_set_arguments(_mock_call_t *call, _mock_variable_t *argv);

uint32_t _mock_call_get_call_count(const _mock_call_t *call);

_mock_value_t _mock_call_get_return_value(const _mock_call_t *call);

_mock_variable_t * _mock_call_get_argv(_mock_call_t *call, _mock_variable_t *arguments);

uint8_t _mock_call_get_argc(_mock_call_t *call);

int _mock_call_arg_matcher(void *call, void *args);


#ifdef __cplusplus
};
#endif

#endif //TESTABLE_MOCK_CALL_H
