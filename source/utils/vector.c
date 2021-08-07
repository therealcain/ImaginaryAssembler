#include "../../include/utils/vector.h"

#include "../../include/utils/debug_print.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define VECTOR_PREFIX "Vector"

GenericVector construct_vector()
{
    GenericVector vec;
    vec.index     = 0;
    vec.max_size  = 1;
    vec.p_data = (void**)malloc(vec.max_size * sizeof(void*));
    
    if(vec.p_data == NULL)
    {
        debug_print(LOG_ERROR, "Error:\n");
        fprintf(stderr, "[%s] Failed to allocate memory for data!\n", VECTOR_PREFIX);
    }

    return vec;
}

/* ------------------------------------------------------------------------- */

void vector_push_back(GenericVector* p_vec, void* p_data)
{
    assert(p_vec);

    if(p_vec->index >= p_vec->max_size)
    {
        void** block = (void**)realloc(p_vec->p_data, sizeof(void*) * (p_vec->max_size * 2));

        if(block == NULL)
        {
            debug_print(LOG_ERROR, "Error:\n");
            fprintf(stderr, "[%s] Failed to reallocate memory for data! leaves unchange.\n", VECTOR_PREFIX);
            return;
        }
        else
            p_vec->p_data = block;

        p_vec->max_size *= 2;
    }

    p_vec->p_data[p_vec->index] = p_data;
    p_vec->index++;
}

/* ------------------------------------------------------------------------- */

void* vector_at(GenericVector* p_vec, size_t index)
{
    assert(p_vec);

    if(index >= p_vec->max_size)
    {
        debug_print(LOG_ERROR, "Error:\n");
        fprintf(stderr, "[%s] Index is too big! (%ld >= %ld)\n", VECTOR_PREFIX, index, p_vec->max_size);
        
        return NULL;
    }

    return p_vec->p_data[index];
}

/* ------------------------------------------------------------------------- */

void vector_clear(GenericVector* p_vec)
{
    assert(p_vec);
    free(p_vec->p_data);
}

/* ------------------------------------------------------------------------- */

size_t vector_size(GenericVector* p_vec)
{
    assert(p_vec);
    return p_vec->index;
}
