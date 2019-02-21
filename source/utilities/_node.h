//
// Created by Andrew Wade on 6/30/18.
//

#ifndef TESTABLE_UTIL_H
#define TESTABLE_UTIL_H

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NODE
#define NODE _node_t
#endif

#ifndef NODE_POOL_SIZE
#define NODE_POOL_SIZE 512
#endif

typedef struct _node_t _node_t;

struct _node_t {
    VOID *data;       /* user data */
    _node_t *prev;       /* prev node in list */
    _node_t *next;       /* next node in list */
};

typedef INT (*_comparator_t)(VOID *lhs, VOID *rhs);

/**
 * Allocate a new node
 * @return
 */
_node_t *_node_allocate();

/**
 * Release a prevly allocated node
 * @param node
 */
VOID _node_release(_node_t *node);

/**
 * Initialize a node with user data
 * @param node Node to initialize
 * @param data User data for node to contain
 */
VOID _node_initialize(_node_t *node, VOID *data);



/**
 * Next Node access
 */
#define _node_next(node) ((node)->next)

/**
 * Previous node access
 */
#define _node_prev(node) ((node)->prev)

/**
 * Data access
 */
#define _node_data(node) ((node)->data)

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_UTIL_H
