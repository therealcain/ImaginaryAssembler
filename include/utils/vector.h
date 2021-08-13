#ifndef VECTOR_GUARD_H
#define VECTOR_GUARD_H

#include "stdint.h"

typedef struct {
    void** p_data;
    size_t index;
    size_t max_size;
} GenericVector;

/* Allocating internal memory and initializing variables. */
extern GenericVector construct_vector();

/* Pushing a value to the vector. */
extern void vector_push_back(GenericVector* p_vec, void* p_data);

/* Retrieving a pointer to data in the vector at index. */
extern void* vector_at(GenericVector* p_vec, size_t index);

/* Cleaning up vector internals. */
extern void vector_clear(GenericVector* p_vec);

/* Get vector size. */
extern size_t vector_size(const GenericVector* p_vec);

#endif /* VECTOR_GUARD_H */
