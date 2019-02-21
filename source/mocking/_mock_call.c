//
// Created by Andrew Wade on 2019-01-10.
//

#include <string.h>
#include <asserts.h>
#include "_mock_call.h"
#include "../utilities/_pool.h"


_mock_call_t mock_call_buffer[MOCK_CALL_BUFFER_SIZE];
_mock_variable_t mock_variable_buffer[MOCK_CALL_BUFFER_SIZE];
uint8_t mock_byte_buffer[MOCK_BYTE_BUFFER_SIZE];

_pool_t mock_call_pool;
_pool_t mock_variable_pool;
_pool_t mock_byte_pool;



_mock_call_t *allocate_call() {
    _mock_call_t *call;
    if(!_pool_is_valid(&mock_call_pool)) {
        _pool_init(&mock_call_pool, sizeof(_mock_call_t), mock_call_buffer, mock_call_buffer+MOCK_CALL_BUFFER_SIZE);
    }
    call = _pool_allocate(&mock_call_pool);
    ASSERT_PTR_NOT_NULL(call);
    return call;
}

void release_call(_mock_call_t *call) {
    _pool_release(&mock_call_pool, call);
}

_mock_variable_t *allocate_variables(unsigned count) {
    _mock_variable_t *variables;
    if(!_pool_is_valid(&mock_variable_pool)) {
        _pool_init(&mock_variable_pool, sizeof(_mock_variable_t), mock_variable_buffer, mock_variable_buffer+MOCK_CALL_BUFFER_SIZE);
    }
    variables = _pool_allocate_size(&mock_variable_pool, sizeof(_mock_variable_t)*count);
    ASSERT_PTR_NOT_NULL(variables);
    return variables;
}

void release_variables(_mock_variable_t *variables, unsigned  count) {
    _pool_ordered_release_size(&mock_variable_pool, variables, count*sizeof(_mock_variable_t));
}

void *allocate_bytes(SIZE size) {
    void *bytes;
    if(!_pool_is_valid(&mock_byte_pool)) {
        _pool_init(&mock_byte_pool, sizeof(VOID*), mock_byte_buffer, mock_byte_buffer+MOCK_BYTE_BUFFER_SIZE);
    }
    bytes = _pool_allocate_size(&mock_byte_pool, size);
    ASSERT_PTR_NOT_NULL(bytes);
    return bytes;
}

void release_bytes(void *bytes, SIZE size) {
    _pool_ordered_release_size(&mock_byte_pool, bytes, size);
}

void _mock_value_deep_copy(_mock_value_t *dest, const _mock_value_t *src) {
    dest->type = src->type;
    dest->size = src->size;
    if(dest->address == NULL) {
        dest->address = allocate_bytes(src->size);
    }
    if(src->address != NULL) {
        memcpy(dest->address, src->address, src->size);
    }
}

void _mock_value_destroy(_mock_value_t *value) {
    release_bytes(value->address, sizeof(_mock_value_t));
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

_mock_call_t * _mock_call_create(const char *file, uint32_t line, _mock_value_t returns, _mock_variable_t *argv, uint8_t argc) {
    _mock_call_t *new_call = allocate_call();
    if(new_call != NULL) {
        new_call->file = file;
        new_call->line = line;
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

    release_variables(call->argv, call->argc);
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
        call->argv = allocate_variables(call->argc);
    }

    for (uint8_t i = 0; i < call->argc; i++) {
        _mock_variable_deep_copy(&call->argv[i], &argv[i]);
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