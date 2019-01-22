//
// Created by Andrew Wade on 2019-01-22.
//

#ifndef TESTABLE_LIST_H
#define TESTABLE_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "_node.h"

/**
 * Insert node into list
 * @param head Front of list
 * @param node New node to insert
 */
void _list_insert(_node_t *head, _node_t *node);

void _list_append(_node_t *head, void *data);

void *_list_find_match(_node_t *head, _node_matcher_t matcher, void *data);

/**
 * Remove node from its list
 * @param node Node to remove
 */
void _list_remove(_node_t *node);

/**
 *
 * @param node
 * @param predicate
 */
_node_t *_list_filter(_node_t *node, int (*predicate)(_node_t *node));


#define _list_last(node) ((node)->prev)
#ifdef __cplusplus
};
#endif

#endif //TESTABLE_LIST_H
