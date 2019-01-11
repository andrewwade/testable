//
// Created by Andrew Wade on 4/22/18.
//

#include <stdlib.h>
#include "_pool.h"

#define pool_contains_data(pool, data) ((data) >= (pool)->memory && (data) < (pool)->memory + (pool)->size)

#define pool_data_aligned(pool, data) (((data) - (pool)->memory) % (pool)->alignment == 0)

#define pool_valid(pool) ( \
        (pool) != NULL && \
        (pool)->memory != NULL && \
        (pool)->alignment >= sizeof(void *) && \
        (pool)->size >= (pool)->alignment && \
        ((pool)->head == NULL || pool_contains_data((pool), (pool)->head)))

#define pool_invalid(pool) (!pool_valid(pool))


void *malloc_aligned(size_t size, size_t alignment) {
    void   *p1, *p2;
    size_t addr;

    if (alignment == 0) {
        return NULL;
    }

    if ((p1 = malloc(size + sizeof(void *) + alignment - 1)) == NULL) {
        return NULL;
    }

    addr = (size_t) p1 + sizeof(void *) + alignment - 1;
    p2   = (void *) (addr - (addr % alignment));

    *((size_t *) p2 - 1) = (size_t) p1;

    return p2;
}

void free_aligned(void *data) {
    free((void *) (*((size_t *) data - 1)));
}


int pool_init(pool_t *pool, void *memory, unsigned int size, unsigned int alignment) {
    if (pool == NULL) { return -1; }
    if (alignment < sizeof(void *)) { return -1; }
    if (size < alignment || size % alignment != 0) { return -1; }

    pool->alignment = alignment;
    pool->size      = size;
    pool->memory    = memory;

    /* create memory memory if needed*/
    if (pool->memory == NULL && (pool->memory = malloc(pool->size)) == NULL) {
        return -1;
    }

    /* assign head to front of memory */
    pool->head = pool->memory;

    /* initialize memory into a stack where each element points to the next element*/
    char *element;
    for (element = pool->memory; size > alignment; element += alignment, size -= alignment) {
        *(void **) element = element + alignment;
    }

    /* set last element value to NULL to indicate end of memory*/
    *(void **) element = NULL;

    return 0;
}

void *pool_alloc(pool_t *pool) {
    if (pool_invalid(pool)) {
        return NULL;
    }
    if (pool_empty(pool)) {
        return NULL;
    }

    void *data = pool->head;
    pool->head = *(void **) pool->head;
    return data;
}

void pool_free(pool_t *pool, void *data) {
    if (pool_invalid(pool)) {
        return;
    }

    /* data address can't be outside of memory */
    if (!pool_contains_data(pool, data)) {
        return;
    }

    /* data address can't be misaligned */
    if (!pool_data_aligned(pool, data)) {
        return;
    }

    /* push onto stack */
    void *temp = pool->head;
    pool->head = data;
    *(void **) pool->head = temp;
}

void pool_destroy(pool_t *pool) {
    if (pool_invalid(pool)) {
        return;
    }
    free(pool->memory);
    pool->memory    = NULL;
    pool->head      = NULL;
    pool->alignment = 0;
    pool->size      = 0;
}