//
// Created by Andrew Wade on 2019-01-22.
//

#include "_stack.h"

#define _stack_empty(stack) ((stack)->elements == NULL)

VOID _stack_init(_stack_t *self, VOID *owner) {
    self->owner = owner;
    self->size = 0;
    self->elements = NULL;
}

VOID* _stack_pop(_stack_t *self) {
    VOID *element = NULL;
    _node_t *top = self->elements;
    if(top != NULL) {
        element = top->data;
        top->next->prev = top->prev;
        top->prev->next = top->next;
        self->elements = top->next;
        _node_release(top);
        self->size--;
    }
    return element;
}

VOID _stack_push(_stack_t *self, VOID *element) {
    _node_t *top = _node_allocate();
    if(top != NULL) {
        _node_initialize(top, element);
        if(self->elements != NULL) {
            top->next = self->elements;
            top->prev = self->elements->prev;
            top->prev->next = top;
            top->next->prev = top;
        }
        self->elements = top;
        self->size++;
    }
}

VOID *_stack_top(_stack_t *self) {
    VOID *element = NULL;
    if(!_stack_empty(self)) {
        element = _node_data(self->elements);
    }
    return element;
}

VOID *_stack_bottom(_stack_t *self) {
    VOID *element = NULL;
    if (!_stack_empty(self)) {
        element = _node_data(_node_prev(self->elements));
    }
    return element;
}

VOID _stack_clear(_stack_t *self) {
    while(self->size > 0) {
        _stack_pop(self);
    }
}

SIZE _stack_size(_stack_t *self) {
    return self->size;
}

VOID *_stack_owner(_stack_t *self) {
    return self->owner;
}