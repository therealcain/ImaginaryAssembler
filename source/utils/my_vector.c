#include "utils/my_vector.h"
#include "utils/debug_print.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define VECTOR_PREFIX "Vector"
#define INITIAL_SIZE 5

GenericVector* allocate_vector()
{
    GenericVector* p_vec = (GenericVector*)malloc( sizeof( GenericVector ) );

    if( p_vec == NULL )
    {
        debug_print( LOG_ERROR, "Error:\n" );
        fprintf( stderr, "[%s] Failed to allocate memory for vector!\n", VECTOR_PREFIX );

        return NULL;
    }

    p_vec->last     = 0;
    p_vec->capacity = INITIAL_SIZE;
    p_vec->p_data   = (void**)malloc( INITIAL_SIZE * sizeof( void* ) );

    if( p_vec->p_data == NULL )
    {
        debug_print( LOG_ERROR, "Error:\n" );
        fprintf( stderr, "[%s] Failed to allocate memory for vector data!\n", VECTOR_PREFIX );

        free( p_vec );
        p_vec = NULL;

        return NULL;
    }

    return p_vec;
}

/* ------------------------------------------------------------------------- */

void vector_push_back( GenericVector* p_vec, void* p_data )
{
    assert( p_vec );

    if( p_vec->last >= p_vec->capacity )
    {
        const size_t new_size = p_vec->capacity * 2;
        void** block = (void**)realloc( p_vec->p_data, sizeof( void* ) * new_size );

        if( block == NULL )
        {
            debug_print( LOG_ERROR, "Error:\n" );
            fprintf( stderr, "[%s] Failed to reallocate memory for data! leaves unchanged.\n", VECTOR_PREFIX );
            return;
        }
        else
            p_vec->p_data = block;

        p_vec->capacity = new_size;
    }

    p_vec->p_data[ p_vec->last ] = p_data;
    p_vec->last++;
}

/* ------------------------------------------------------------------------- */

void* vector_at( GenericVector* p_vec, size_t index )
{
    assert( p_vec );

    if( index >= p_vec->last )
    {
        debug_print( LOG_ERROR, "Error:\n" );
        fprintf( stderr, "[%s] Index is too big! (%ld >= %ld)\n", VECTOR_PREFIX, index, p_vec->last );

        return NULL;
    }

    return p_vec->p_data[ index ];
}

/* ------------------------------------------------------------------------- */

void vector_clear( GenericVector* p_vec )
{
    assert( p_vec );

    memset( p_vec->p_data, 0, p_vec->capacity );
    free( p_vec->p_data );

    free( p_vec );
    p_vec = NULL;
}

/* ------------------------------------------------------------------------- */

size_t vector_size( const GenericVector* p_vec )
{
    assert( p_vec );
    return p_vec->last;
}

/* ------------------------------------------------------------------------- */

ssize_t vector_find( const GenericVector* p_vec, void* p_data )
{
    ssize_t i;

    assert( p_vec );

    for( i = 0; i < p_vec->last; i++ )
    {
        if( p_vec->p_data[ i ] == p_data )
            return i;
    }

    return -1;
}

/* ------------------------------------------------------------------------- */

bool vector_remove_by_index( GenericVector* p_vec, size_t index )
{
    size_t i;

    assert( p_vec );

    if( index >= p_vec->last )
        return false;

    for( i = index; i < p_vec->last - 1; i++ )
        p_vec->p_data[ i ] = p_vec->p_data[ i + 1 ];

    p_vec->last--;

    return true;
}

/* ------------------------------------------------------------------------- */

bool vector_remove_by_ptr( GenericVector* p_vec, void* p_data )
{
    ssize_t index;
    assert( p_vec );

    index = vector_find( p_vec, p_data );

    return index == -1 ? false : vector_remove_by_index( p_vec, index );
}
