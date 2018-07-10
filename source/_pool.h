//
// Created by Andrew Wade on 4/22/18.
//

#ifndef TESTING_POOL_H
#define TESTING_POOL_H


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Pool structure for polymorphic usage
 *
 * @var memory      pointer to pool memory block
 * @var head        pointer to first free element in pool memory
 * @var alignment   aligned size of 1 element in pool. minimum size is the size of a pointer
 * @var size        total number of elements after initialization
 */
typedef struct {
    void         *memory;
    void         *head;
    unsigned int alignment;
    unsigned int size;
} pool_t;

/**
 * Initialize a pool struct
 * @param pool      pool to initialize
 * @param memory    contiguous block of memory for pool to use must be >= sizeof(void*)
 * @param size      size of memory. must be multiple of alignment
 * @param alignment size of single element in pool. must be >= sizeof(void*)
 * @return
 */

int pool_init(pool_t *pool, void *memory, unsigned int size, unsigned int alignment);

/**
 * Allocate 1 element from pool
 * @param pool      pool to get element from
 * @return          pointer to element or NULL if no element was allocated
 */
void *pool_alloc(pool_t *pool);

/**
 * Release 1 element back to the pool for reuse
 * @param pool      pool that element was allocated from
 * @param data      element to put back into pool
 */
void pool_free(pool_t *pool, void *data);

/**
 * Destroy a pool
 * @param pool
 */
void pool_destroy(pool_t *pool);
/**
 * Check if pool is empty
 * @param pool      pointer to pool_t structure
 */
#define pool_empty(pool) ((pool)->head == NULL)

#ifdef __cplusplus
};
#endif

#endif //PROTOSTACK_TEST_POOL_H
