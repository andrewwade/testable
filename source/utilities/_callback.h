//
// Created by Andrew Wade on 2019-02-16.
//

#ifndef TESTABLE_CALL_H
#define TESTABLE_CALL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "_list.h"


typedef struct callback_t callback_t;

struct callback_t {
    void *owner;
    void (*call)(void *owner, void *data);
};

typedef struct call_stack_t call_stack_t;
typedef struct call_chain_t call_chain_t;
typedef void (*call_t)(void *);

struct call_chain_t {
    void *owner;
    _node_t *calls;
};



void _call_chain_init(call_chain_t *self, void *owner);

void _call_chain_append(call_chain_t *self, call_t *call);

void _call_chain_remove(call_chain_t *self, call_t *call);

void _call_chain_call(call_chain_t *self, void *data);

struct call_stack_t {
    void *owner;
    _node_t *calls;
};

void _call_stack_init(call_stack_t *self, void *owner);

void _call_stack_push(call_stack_t *self, call_t *call);

call_t *_call_stack_pop(call_stack_t *self);

void _call_stack_call_top(call_stack_t *self);

void _call_stack_call(call_stack_t *self);


#ifdef __cplusplus
};
#endif

#endif //TESTABLE_CALL_CHAIN_H
