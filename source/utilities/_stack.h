//
// Created by Andrew Wade on 2019-01-22.
//

#ifndef TESTABLE_STACK_H
#define TESTABLE_STACK_H

#include "_node.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _stack_t _stack_t;


struct _stack_t {
    VOID *owner;
    NODE *elements;
    SIZE size;
};

#define STACK _stack_t

VOID _stack_init(_stack_t *self, void *owner);

VOID* _stack_pop(_stack_t *self);

VOID _stack_push(_stack_t *self, void *element);

VOID *_stack_top(_stack_t *self);

VOID *_stack_bottom(_stack_t *self);

VOID _stack_clear(_stack_t *self);

SIZE _stack_size(_stack_t *self);

VOID *_stack_owner(_stack_t *self);

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_STACK_H
