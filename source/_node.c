//
// Created by Andrew Wade on 7/1/18.
//

#include <stddef.h>
#include <testable.h>
#include "_node.h"
#include "_pool.h"

static _node_t pool_buffer[NODE_POOL_SIZE];
static pool_t  pool;


void _node_pool_initialize() {
    pool_init(&pool, pool_buffer, NODE_POOL_SIZE * sizeof(_node_t), sizeof(_node_t));
}

void *_node_allocate() {
    _node_t *new_node;

    /* initialize pool if required */
    if (pool.memory != pool_buffer) {
        _node_pool_initialize();
    }

    /* get new node from front of free list */
    new_node = pool_alloc(&pool);

    return new_node;
}

void _node_release(_node_t *node) {
    pool_free(&pool, node);
}

void _node_initialize(_node_t *node, void *data) {

    /* check that node is not NULL */
    ASSERT_PTR_NE(NULL, node, "Node cannot be NULL");

    node->data = data;

    /* set node as single element circular list */
    node->next = node;
    node->prev = node;
}

void _node_insert(_node_t *head, _node_t *node) {
    ASSERT_PTR_NE(NULL, head);
    ASSERT_PTR_NE(NULL, node);

    /* link node to head */
    node->next = head;

    /* link node to tail */
    node->prev = head->prev;

    /* link tail to node */
    head->prev->next = node;

    /* link head to node */
    head->prev = node;
}

void _node_remove(_node_t *node) {

    /* check for null node */
    if (node == NULL) {
        return;
    }

    /* link prev to next */
    node->prev->next = node->next;

    /* link_next to prev */
    node->next->prev = node->prev;
}

_node_t *_node_filter(_node_t *head, int (*except)(_node_t *node)) {
    _node_t *filtered;
    _node_t *unfiltered;

    if (head == NULL || except == NULL) {
        return NULL;
    }

    unfiltered = head;
    filtered   = NULL;
    do {
        if (except(unfiltered)) {
            _node_t *copy = _node_allocate();
            _node_initialize(copy, unfiltered->data);
            if (filtered == NULL) {
                filtered = copy;
            } else {
                _node_insert(filtered, copy);
            }
        }
        unfiltered = unfiltered->next;
    } while (unfiltered != NULL && unfiltered != head);
    return filtered;
}