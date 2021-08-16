#ifndef MY_VECTOR_GUARD_H
#define MY_VECTOR_GUARD_H

#include "my_inttypes.h"
#include "my_bool.h"

typedef struct {
    void** p_data;
    size_t last;
    size_t capacity;
} GenericVector;

#ifdef __cplusplus
extern "C" {
#endif

    /* Allocating internal memory and initializing variables. */
    extern GenericVector* allocate_vector();

    /* Pushing a value to the vector. */
    extern void vector_push_back( GenericVector* p_vec, void* p_data );

    /* Retrieving a pointer to data in the vector at index. */
    extern void* vector_at( GenericVector* p_vec, size_t index );

    /* Cleaning up vector internals. */
    extern void vector_clear( GenericVector* p_vec );

    /* Get vector size. */
    extern size_t vector_size( const GenericVector* p_vec );

    /* Find index of data in the vector. */
    extern ssize_t vector_find( const GenericVector* p_vec, void* p_data );

    /* Remove data by index in the vector. */
    extern bool vector_remove_by_index( GenericVector* p_vec, size_t index );

    /* Find pointer and remove it from the vector. */
    extern bool vector_remove_by_ptr( GenericVector* p_vec, void* p_data );

#ifdef __cplusplus
}
#endif

#endif /* MY_VECTOR_GUARD_H */
