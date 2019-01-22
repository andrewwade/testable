//
// Created by Andrew Wade on 2019-01-20.
//

#include <stdbool.h>
#include "_pool.h"
#include "asserts.h"

static VOID _pool_segment(VOID *memory, SIZE alignment, SIZE size, BOOL null_ending);

VOID _pool_init(_pool_t *pool, SIZE alignment, VOID *start, VOID *end) {
    ASSERT_PTR_NOT_NULL(pool, "Cannot initialize a null pool pointer");
    ASSERT_ULONG_GE(sizeof(VOID*), alignment, "Alignment must be larger than sizeof(VOID*)");
    ASSERT_PTR_NOT_NULL(start, "Pool buffer start cannot be null");
    ASSERT_PTR_NOT_NULL(end, "Pool buffer end cannot be null");
    ASSERT_ULONG_EQ(0, (end-start)%alignment, "Pool Buffer not aligned");

    pool->alignment = (alignment < sizeof(VOID*)) ? sizeof(VOID*) : alignment;
    pool->start = start;
    pool->search = start;
    pool->end = end;

    _pool_segment(pool->start, pool->alignment, pool->end-pool->start, true);
    pool->search = pool->start;
}

BOOL _pool_is_valid(_pool_t *pool) {
    return (pool != NULL)
    && (pool->alignment >= sizeof(VOID*))
    && (pool->start != NULL)
    && (pool->end != NULL)
    && (((pool->end - pool->start)%pool->alignment) == 0)
    && (pool->start <= pool->search && pool->search <= pool->end);
}


BOOL _pool_empty(_pool_t *pool) {
    ASSERT_PTR_NOT_NULL(pool);
    return (pool == NULL) || (pool->start == NULL) ||(pool->search == NULL);
}

VOID *_pool_allocate(_pool_t *pool) {
    ASSERT_PTR_NOT_NULL(pool);
    VOID *return_ptr = pool->search;
    if(pool->search) {
        pool->search = *(VOID **)pool->search;
    }
    return return_ptr;
}

VOID _pool_release(_pool_t *pool, VOID *memory) {
    ASSERT_PTR_NOT_NULL(pool);
    ASSERT_PTR_NOT_NULL(memory);
    *(CHAR **)memory = pool->search;
    pool->search = memory;
}

VOID _pool_ordered_release(_pool_t *pool, VOID *memory) {
    ASSERT_PTR_NOT_NULL(pool);
    ASSERT_PTR_NOT_NULL(memory);
    VOID *search = pool->search;
    VOID *next;

    while(search != NULL) {
        next = *(CHAR**)search;
        if(search < memory && memory < next) {
            *(CHAR**)memory = next;
            *(CHAR**)search = memory;
            search = NULL; /*done searching */
        } else {
            search = next;
        }
    }
}

VOID *_pool_allocate_size(_pool_t *pool, SIZE size) {
    ASSERT_PTR_NOT_NULL(pool);
    ASSERT(size > 0);

    VOID *search = pool->search;
    VOID *next;
    VOID *return_ptr= NULL;
    SIZE available = 0;

    while(search != NULL && available < size) {
        next = *(CHAR**)search;
        if(next == search+pool->alignment) {
            /* this is free */
            available += pool->alignment;
        } else {
            available = 0;
        }
        search = next;
    }

    if(available >= size) {
        pool->search = search;
        return_ptr = search-available;
    }

    return return_ptr;
}

VOID _pool_release_size(_pool_t *pool, VOID *memory, SIZE size) {
    ASSERT_PTR_NOT_NULL(pool);
    ASSERT_PTR_NOT_NULL(memory);
    ASSERT(size > 0);
    _pool_segment(memory, pool->alignment, size - pool->alignment, true);
    *(CHAR**)(memory+size-pool->alignment) = pool->search;
    pool->search = memory;
}

VOID _pool_ordered_release_size(_pool_t *pool, VOID *memory, SIZE size) {
    ASSERT_PTR_NOT_NULL(pool);
    ASSERT_PTR_NOT_NULL(memory);
    ASSERT_ULONG_GE(0, size);
    ASSERT(size > 0);

    VOID *search = pool->search;
    VOID *next;

    while(search != NULL) {
        next = *(CHAR**)search;
        if(search < memory && memory < next) {
            _pool_segment(memory, pool->alignment, size - pool->alignment, true);
            *(CHAR**)(memory+size-pool->alignment) = pool->search;
            pool->search = memory;
            search = NULL; /*done searching */
        } else {
            search = next;
        }
    }
}

static VOID _pool_segment(VOID *memory, SIZE alignment, SIZE size, BOOL null_ending) {
    ASSERT_PTR_NOT_NULL(memory);
    ASSERT_ULONG_GE(sizeof(VOID*), alignment);
    ASSERT_ULONG_GE(0, size);

    for(SIZE i = 0; i < size-alignment; i += alignment) {
        *(CHAR**)memory = memory+alignment;
        memory = *(CHAR**)memory;
    }

    if(null_ending) {
        *(CHAR **) memory = NULL; /* null terminated end */
    }
}