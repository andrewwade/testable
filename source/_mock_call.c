//
// Created by Andrew Wade on 2019-01-10.
//

#include <string.h>
#include "_mock_call.h"
#include "byte_pool.h"
#include "block_pool.h"

extern byte_pool_t *mock_byte_pool;
extern block_pool_t *mock_call_pool;

void _mock_value_deep_copy(_mock_value_t *dest, const _mock_value_t *src) {
    dest->type = src->type;
    dest->size = src->size;
    if(dest->address == NULL) {
        dest->address = byte_allocate(mock_byte_pool, src->size);
    }
    if(src->address != NULL) {
        memcpy(dest->address, src->address, src->size);
    }
}

void _mock_value_destroy(_mock_value_t *value) {
    byte_release(value->address);
    value->address = NULL;
    value->size = 0;
    value->type = NULL;
}

void _mock_variable_deep_copy(_mock_variable_t *dest, const _mock_variable_t *src) {
    dest->name = src->name;
    _mock_value_deep_copy(&dest->value, &src->value);
}

void _mock_variable_destroy(_mock_variable_t *variable) {
    _mock_value_destroy(&variable->value);
    variable->name = NULL;
}

_mock_call_t * _mock_call_create(_mock_value_t returns, _mock_variable_t *argv, uint8_t argc) {
    _mock_call_t *new_call = block_allocate(mock_call_pool);
    if(new_call != NULL) {
        new_call->call_count = 0;
        new_call->callback   = NULL;
        new_call->argv       = NULL;
        new_call->argc       = argc;
        _mock_call_set_return_value(new_call, returns);
        _mock_call_set_arguments(new_call, argv);
    }
    return new_call;
}

void _mock_call_destroy(_mock_call_t * call) {
    _mock_value_destroy(&call->return_value);
    for(uint8_t i = 0; i < call->argc; i++) {
        _mock_variable_destroy(&call->argv[i]);
    }

    byte_release(call->argv);
    call->argv = NULL;
    call->argc = 0;
    call->callback = NULL;
    call->call_count = 0;
}

void _mock_call_set_call_count(_mock_call_t *call, uint32_t count) {
    call->call_count = count;
}

void _mock_call_increment_call_count(_mock_call_t *call) {
    call->call_count++;
}

void _mock_call_decrement_call_count(_mock_call_t *call) {
    call->call_count--;
}

void _mock_call_set_return_value(_mock_call_t *call, _mock_value_t value) {
    _mock_value_deep_copy(&call->return_value, &value);
}

void _mock_call_set_arguments(_mock_call_t *call, _mock_variable_t *argv) {
    if(call->argv == NULL && call->argc > 0) {
        call->argv = byte_allocate(mock_byte_pool, sizeof(_mock_variable_t)*call->argc);
    }
    if(call->argv != NULL) {
        for (uint8_t i = 0; i < call->argc; i++) {
            _mock_variable_deep_copy(&call->argv[i], &argv[i]);
        }
    }
}

uint32_t _mock_call_get_call_count(const _mock_call_t *call) {
    return call->call_count;
}

_mock_value_t _mock_call_get_return_value(const _mock_call_t *call) {
    return call->return_value;
}

_mock_variable_t * _mock_call_get_argv(_mock_call_t *call, _mock_variable_t *arguments) {
    return call->argv;
}

uint8_t _mock_call_get_argc(_mock_call_t *call) {
    return call->argc;
}

int _mock_call_compare_args(_mock_call_t *call, _mock_variable_t *argv) {
    int difference = 0;
    for(uint8_t i = 0; i < call->argc; i++) {
        difference += strcmp(call->argv[i].name, argv->name);
        difference += strcmp(call->argv[i].value.type, argv[i].value.type);
        difference += (call->argv[i].value.size != argv[i].value.size);
        difference += memcmp(call->argv[i].value.address, argv[i].value.address, argv[i].value.size);
    }
    return difference;
}


int _mock_call_arg_matcher(void *call, void *argv) {
    return _mock_call_compare_args(call, argv);
}