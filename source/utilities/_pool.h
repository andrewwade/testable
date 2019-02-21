//
// Created by Andrew Wade on 2019-01-22.
//

#ifndef TESTABLE_POOL_H
#define TESTABLE_POOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "platform.h"

typedef struct _pool_t _pool_t;

struct _pool_t {
    VOID *start;
    VOID *search;
    VOID *end;
    SIZE alignment;
};

VOID _pool_init(_pool_t *pool, SIZE alignment, VOID *start, VOID *end);

BOOL _pool_is_valid(_pool_t *pool);

VOID *_pool_allocate(_pool_t *pool);

VOID _pool_release(_pool_t *pool, VOID *memory);

VOID _pool_ordered_release(_pool_t *pool, VOID *memory);

VOID *_pool_allocate_size(_pool_t *pool, SIZE size);

VOID _pool_release_size(_pool_t *pool, VOID *memory, SIZE size);

VOID _pool_ordered_release_size(_pool_t *pool, VOID *memory, SIZE size);

BOOL _pool_empty(_pool_t *pool);

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_POOL_H
