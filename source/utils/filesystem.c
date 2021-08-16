#include "utils/filesystem.h"
#include "utils/string_utils.h"
#include "utils/predefs.h"

#include <stdio.h>

#ifdef PLATFORM_WINDOWS
static const char seperator = '\\';
#else
static const char seperator = '/';
#endif

/* ------------------------------------------------------------------------- */

char* get_filename_without_extension_from_path( const char* path )
{
    const char* extension = get_filename_extension( path );
    const char* filename  = get_last_substring_by_delimiter( path, seperator );

    return extension == path ?
        copy_string( filename ) :
        get_substring( filename, 0, strlen( filename ) - strlen( extension ) - 1 );
}

/* ------------------------------------------------------------------------- */

const char* get_filename_extension( const char* path )
{
    return get_last_substring_by_delimiter( path, '.' );
}

/* ------------------------------------------------------------------------- */

bool can_read_file( const char* path )
{
    FILE* fp;
    if( (fp = fopen( path, "rb" )) != NULL )
    {
        fclose( fp );
        return true;
    }

    return false;
}
