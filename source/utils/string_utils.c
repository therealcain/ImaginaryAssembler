#include "utils/string_utils.h"

#include <stdlib.h>
#include <assert.h>

char* get_substring( const char* string, size_t begin, size_t end )
{
    int32_t size;
    char* substr;

    assert( string );

    size = end - begin;

    if( size <= 0 )
        return NULL;

    substr = (char*)malloc( size + 1 );
    if( substr == NULL )
        return NULL;

    strncpy( substr, string + begin, size );
    substr[ size ] = '\0';

    return substr;
}

/* ------------------------------------------------------------------------- */

const char* get_last_substring_by_delimiter( const char* string, char delimiter )
{
    const char* ret;

    assert( string );

    ret = strrchr( string, delimiter );

    if( ret == NULL )
        ret = string;
    else
        ret++;

    return ret;
}

/* ------------------------------------------------------------------------- */

void buffer_concatenate_string( char* dest, size_t len, const char* src1, const char* src2 )
{
    assert( len > strlen( src1 ) + strlen( src2 ) );
    assert( dest );

    strcpy( dest, src1 );
    strcat( dest, src2 );
}

/* ------------------------------------------------------------------------- */

char* copy_string( const char* string )
{
    return get_substring( string, 0, strlen( string ) );
}
