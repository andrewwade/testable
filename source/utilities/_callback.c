//
// Created by Andrew Wade on 2019-02-16.
//

#include "_callback.h"

void _call_chain_init(call_chain_t *self, void *owner) {
    self->owner = owner;
    self->calls = NULL;
}

void _call_chain_append(call_chain_t *self, call_t *call) {
    _node_t *new_call_node = _node_allocate();
    if(new_call_node != NULL) {
        _node_initialize(new_call_node, call);
        _list_append(self->calls, new_call_node);
    }
}

void _call_chain_remove(call_chain_t *self, call_t *call) {

}

void _call_chain_call(call_chain_t *self, void *data);