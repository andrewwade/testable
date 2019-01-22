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

typedef int (*_node_matcher_t)(void *node_data, void *matcher_data);

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
