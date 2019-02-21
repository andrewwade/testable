//
// Created by Andrew Wade on 7/1/18.
//

#include <asserts.h>
#include "_node.h"
#include "_pool.h"

static _node_t pool_buffer[NODE_POOL_SIZE];
static _pool_t  pool;


void _node_pool_initialize() {
    _pool_init(&pool, sizeof(_node_t), pool_buffer, pool_buffer+NODE_POOL_SIZE);
}

_node_t *_node_allocate() {
    _node_t *new_node;

    /* initialize pool if required */
    if (!_pool_is_valid(&pool)) {
        _node_pool_initialize();
    }

    /* get new node from front of free list */
    new_node = _pool_allocate(&pool);
    ASSERT_PTR_NOT_NULL(new_node);

    new_node->next = new_node;
    new_node->prev = new_node;

    return new_node;
}

void _node_initialize(_node_t *node, void *data) {

    /* check that node is not NULL */
    ASSERT_PTR_NE(NULL, node, "Node cannot be NULL");

    node->data = data;

    /* set node as single element circular list */
    node->next = node;
    node->prev = node;
}

void _node_release(_node_t *node) {
    node->data = 0;
    node->next = 0;
    node->prev = 0;
    _pool_release(&pool, node);
}