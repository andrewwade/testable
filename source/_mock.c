//
// Created by Andrew Wade on 12/8/18.
//


#include <string.h>
#include "_mock.h"

void _log_mock_call(_mock_t *mock, _mock_variable_t *argv) {
    printf("%s %s(", mock->return_value.type, mock->name);
    for (int i = 0; i < mock->argc; i++) {
        _mock_variable_t *arg = &argv[i];
        printf("%s %s", arg->value.type, arg->name);
    }
    printf("):\n");
}


void *_mock_handle_call(_mock_t *mock, _mock_variable_t *args) {
    _log_mock_call(mock, args);
    _mock_call_t * received_call = _node_find_match(mock->received_calls, _mock_call_arg_matcher, args);
    _mock_call_t * expected_call = _node_find_match(mock->expected_calls, _mock_call_arg_matcher, args);

    if(received_call == NULL) {
        if(expected_call == NULL) {
            received_call = _mock_call_create(mock->return_value, args, mock->argc);
        } else {
            received_call = _mock_call_create(expected_call->return_value, args, mock->argc);
        }
    }

    _mock_call_increment_call_count(received_call);

    if(mock->received_calls == NULL) {
        mock->received_calls = _node_allocate();
        mock->received_calls->data = received_call;
    } else {
        _node_append(mock->received_calls, received_call);
    }

    return received_call->return_value.address;
}

void _mock_expect_call(_mock_t *mock) {
    _mock_call_t *new_expected_call = _mock_call_create(mock->return_value, (_mock_variable_t *) mock->argv, mock->argc);
    new_expected_call->call_count = 1;
    new_expected_call->callback   = NULL;
    if(mock->expected_calls == NULL) {
        mock->expected_calls = _node_allocate();
        mock->expected_calls->data = new_expected_call;
    } else {
        _node_append(mock->expected_calls, new_expected_call);
    }
}

void _mock_expect_call_callback(_mock_t *mock, void *callback) {
    _mock_call_t *expected_call = _mock_get_last_expected_call(mock);
    expected_call->callback = callback;
}

void _mock_expect_call_with_args(_mock_t *mock, _mock_variable_t *args) {
    _mock_call_t *expected_call = _mock_get_last_expected_call(mock);
    _mock_call_set_arguments(expected_call, args);
}

void _mock_expect_call_returns(_mock_t *mock, _mock_value_t return_value) {
    _mock_call_t *expected_call = _mock_get_last_expected_call(mock);
    _mock_call_set_return_value(expected_call, return_value);
}

void _mock_expect_call_times(_mock_t *mock, uint32_t multiplier) {
    _mock_call_t *expected_call = _mock_get_last_expected_call(mock);
    uint32_t     count          = _mock_call_get_call_count(expected_call);
    _mock_call_set_call_count(expected_call, count * multiplier);
}

_mock_call_t *_mock_get_last_expected_call(_mock_t *mock) {
    return _node_data(_node_last(mock->expected_calls));
}

_mock_call_t *_mock_get_last_received_call(_mock_t *mock) {
    return _node_data(_node_last(mock->received_calls));
}
