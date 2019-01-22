//
// Created by Andrew Wade on 7/1/18.
//

#include <stddef.h>
#include <testable.h>
#include "_node.h"
#include "_pool.h"


void _list_insert(_node_t *head, _node_t *node) {
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

void _list_append(_node_t *head, void *data) {
    _node_t *node = _node_allocate();
    node->data = data;
    _list_insert(head, node);
}

void _list_remove(_node_t *node) {

    /* check for null node */
    if (node == NULL) {
        return;
    }

    /* link prev to next */
    node->prev->next = node->next;

    /* link_next to prev */
    node->next->prev = node->prev;
}

_node_t *_list_filter(_node_t *node, int (*predicate)(_node_t *node)) {
    _node_t *filtered;
    _node_t *unfiltered;

    if (node == NULL || predicate == NULL) {
        return NULL;
    }

    unfiltered = node;
    filtered   = NULL;
    do {
        if (predicate(unfiltered)) {
            _node_t *copy = _node_allocate();
            _node_initialize(copy, unfiltered->data);
            if (filtered == NULL) {
                filtered = copy;
            } else {
                _list_insert(filtered, copy);
            }
        }
        unfiltered = unfiltered->next;
    } while (unfiltered != NULL && unfiltered != node);
    return filtered;
}

void *_list_find_match(_node_t *head, _node_matcher_t matcher, void *data) {
    _node_t *curr = head;
    _node_t *return_ptr = NULL;
    if(head != NULL) {
        do {
            if (matcher(curr->data, data) == 0) {
                return_ptr = curr->data;
            }
            curr = curr->next;
        } while (curr != head && return_ptr == NULL);
    }

    return return_ptr;
}