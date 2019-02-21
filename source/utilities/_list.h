//
// Created by Andrew Wade on 2019-01-22.
//

#ifndef TESTABLE_LIST_H
#define TESTABLE_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "_node.h"

typedef struct _list_t _list_t;
typedef struct _iterator_t _iterator_t;

struct _iterator_t {
    void *value;
    _iterator_t *(*next)(_iterator_t *it);
    _iterator_t *(*prev)(_iterator_t *it);
};

struct _list_t {
    VOID    *owner;
    _node_t *elements;
    SIZE    size;
};

VOID _list_init(_list_t *self, VOID *owner);

VOID _list_append(_list_t *self, VOID *data);

VOID _list_remove(_list_t *self, VOID *data);

VOID _list_insert(_list_t *self, INT index, VOID *data);

VOID *_list_first(_list_t *self);

VOID *_list_last(_list_t *self);

SIZE _list_size(_list_t *self);

VOID *_list_find(_list_t *self, INT(*cmp)(VOID *element, VOID *std), VOID *std, INT result);

VOID *_list_find_nth(_list_t *self, UINT n, INT(*cmp)(VOID *element, VOID *std), VOID *std, INT result);

_list_t _list_filter(_list_t *self, BOOL (*predicate)(VOID *element));

VOID _list_for_each(_list_t *self, VOID (*function)(VOID *element, VOID *input), VOID *input);

VOID _list_for_each_index(_list_t *self, VOID (function)(UINT index, VOID *element, VOID *input), VOID *input);

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_LIST_H
