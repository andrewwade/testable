//
// Created by Andrew Wade on 6/30/18.
//

#ifndef TESTABLE_UTIL_H
#define TESTABLE_UTIL_H

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NODE_POOL_SIZE
#define NODE_POOL_SIZE 256
#endif


typedef struct _node_t {
    void           *data;       /* user data */
    struct _node_t *prev;       /* prev node in list */
    struct _node_t *next;       /* next node in list */
} _node_t;

/**
 * Allocate a new node
 * @return
 */
void *_node_allocate();

/**
 * Release a prevly allocated node
 * @param node
 */
void _node_release(_node_t *node);

/**
 * Initialize a node with user data
 * @param node Node to initialize
 * @param data User data for node to contain
 */
void _node_initialize(_node_t *node, void *data);

/**
 * Insert node into list
 * @param head Front of list
 * @param node New node to insert
 */
void _node_insert(_node_t *head, _node_t *node);

/**
 * Remove node from its list
 * @param node Node to remove
 */
void _node_remove(_node_t *node);

/**
 *
 * @param node
 * @param predicate
 */
_node_t *_node_filter(_node_t *node, int (*predicate)(_node_t *node));

/**
 * Next Node access
 */
#define _node_next(node) ((node)->next)

/**
 * Previous node access
 */
#define _node_prev(node) ((node)->prev)

/**
 * Access last node assuming (node) is head
 */
#define _node_last(node) ((node)->prev)

/**
 * Data access
 */
#define _node_data(node) ((node)->data)

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_UTIL_H
