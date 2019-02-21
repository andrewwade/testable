//
// Created by Andrew Wade on 7/1/18.
//

#include <testable.h>


VOID _list_init(_list_t *self, VOID *owner) {
    self->owner    = owner;
    self->size     = 0;
    self->elements = NULL;
}

VOID _list_append(_list_t *self, VOID *data) {
    _node_t *new_list_node = _node_allocate();
    if (new_list_node != NULL) {
        _node_initialize(new_list_node, data);
        if (self->elements == NULL) {
            self->elements = new_list_node;
        } else {
            new_list_node->next       = self->elements;
            new_list_node->prev       = self->elements->prev;
            new_list_node->prev->next = new_list_node;
            new_list_node->next->prev = new_list_node;
        }
        self->size++;
    }
}

VOID _list_remove(_list_t *self, VOID *data) {
    _node_t *node    = self->elements;
    void    *element = NULL;

    if(node != NULL) {
        for (UINT i = 0; i < self->size; i++) {
            if (node->data == data) {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                self->size--;

                if (self->elements == node) {
                    if(self->size == 0) {
                        self->elements = NULL;
                    } else {
                        self->elements = node->next;
                    }
                }
                _node_release(node);

                break;
            }
            node = _node_next(node);
        }
    }
}

#define ABS(value) (value > 0) ? value : -value

VOID _list_insert(_list_t *self, INT index, VOID *data) {
    _node_t *node = self->elements;
    if (ABS(index) <= self->size) {
        _node_t *new_node = _node_allocate();

        if (new_node && node) {
            if (index > 0) {
                for (INT i = 0; i < index; i++) {
                    node = node->next;
                }
            } else {
                for (int i = 0; i > index; i--) {
                    node = node->prev;
                }
            }
            _node_initialize(new_node, data);
            new_node->next       = node;
            new_node->prev       = node->prev;
            new_node->prev->next = new_node;
            new_node->next->prev = new_node;
            self->size++;
        }
        if(node == self->elements) {
            self->elements = new_node;
        }
    }
}


VOID *_list_first(_list_t *self) {
    return self->elements->data;
}

VOID *_list_last(_list_t *self) {
    return self->elements->prev->data;
}

SIZE _list_size(_list_t *self) {
    return self->size;
}

VOID *_list_find(_list_t *self, INT(*cmp)(VOID *element, VOID *std), VOID *std, INT result) {
    SIZE size     = self->size;
    NODE *node    = self->elements;
    VOID *element = NULL;

    for (int i = 0; i < size; i++) {
        if (cmp(node->data, std) == result) {
            element = node->data;
            break;
        }
        node = node->next;
    }
    return element;
}

VOID *_list_find_nth(_list_t *self, UINT n, INT(*cmp)(VOID *element, VOID *std), VOID *std, INT result) {
    SIZE size     = self->size;
    NODE *node    = self->elements;
    VOID *element = NULL;

    for (int i = 0; i < size; i++) {
        if (cmp(node->data, std) == result) {
            if (n == 0) {
                element = node->data;
                break;
            } else {
                n--;
            }
        }
        node = node->next;
    }

    return element;
}

_list_t _list_filter(_list_t *self, BOOL (*predicate)(VOID *element)) {
    _list_t new_list;
    SIZE    size  = self->size;
    NODE    *node = self->elements;

    _list_init(&new_list, self->owner);
    for (SIZE i = 0; i < size; i++) {
        if (predicate(node->data)) {
            _list_remove(self, node);
            _list_append(&new_list, node);
        }
        node = node->next;
    }

    return new_list;
}

VOID _list_for_each(_list_t *self, VOID (*function)(VOID *element, VOID *input), VOID *input) {
    SIZE size  = self->size;
    NODE *node = self->elements;

    for (SIZE i = 0; i < size; i++) {
        function(node->data, input);
        node = node->next;
    }
}

VOID _list_for_each_index(_list_t *self, VOID (function)(UINT index, VOID *element, VOID *input), VOID *input) {
    SIZE size  = self->size;
    NODE *node = self->elements;

    for (UINT i = 0; i < size; i++) {
        function(i, node->data, input);
        node = node->next;
    }
}
//
//void _list_insert(_node_t *head, _node_t *node) {
//    ASSERT_PTR_NE(NULL, head);
//    ASSERT_PTR_NE(NULL, node);
//
//    /* link node to head */
//    node->next = head;
//
//    /* link node to tail */
//    node->prev = head->prev;
//
//    /* link tail to node */
//    head->prev->next = node;
//
//    /* link head to node */
//    head->prev = node;
//}
//
//void _list_append(_node_t *head, void *data) {
//    _node_t *node = _node_allocate();
//    node->data = data;
//    _list_insert(head, node);
//}
//
//void _list_remove(_node_t *node) {
//
//    /* check for null node */
//    if (node == NULL) {
//        return;
//    }
//
//    /* link prev to next */
//    node->prev->next = node->next;
//
//    /* link_next to prev */
//    node->next->prev = node->prev;
//}
//
//_node_t *_list_filter(_node_t *node, int (*predicate)(_node_t *node)) {
//    _node_t *filtered;
//    _node_t *unfiltered;
//
//    if (node == NULL || predicate == NULL) {
//        return NULL;
//    }
//
//    unfiltered = node;
//    filtered   = NULL;
//    do {
//        if (predicate(unfiltered)) {
//            _node_t *copy = _node_allocate();
//            _node_initialize(copy, unfiltered->data);
//            if (filtered == NULL) {
//                filtered = copy;
//            } else {
//                _list_insert(filtered, copy);
//            }
//        }
//        unfiltered = unfiltered->next;
//    } while (unfiltered != NULL && unfiltered != node);
//    return filtered;
//}
//
//void *_list_find_match(_node_t *head, _comparator_t matcher, void *data) {
//    _node_t *curr       = head;
//    _node_t *return_ptr = NULL;
//    if (head != NULL) {
//        do {
//            if (matcher(curr->data, data) == 0) {
//                return_ptr = curr->data;
//            }
//            curr = curr->next;
//        } while (curr != head && return_ptr == NULL);
//    }
//
//    return return_ptr;
//}