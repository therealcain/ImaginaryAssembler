#include "../../include/utils/filesystem.h"
#include "../../include/utils/string.h"
#include "../../include/utils/predefs.h"

#include <stdio.h>

#ifdef PLATFORM_WINDOWS
static const char path_slash = '\\';
#else
static const char path_slash = '/';
#endif

/* ------------------------------------------------------------------------- */

char* get_filename_without_extension_from_path(const char* path)
{
    const char* extension = get_filename_extension(path);
    const char* filename  = get_last_substring_by_delimiter(path, path_slash);
    
    if(extension == path)
        return copy_string(filename);

    return get_substring(filename, 0, strlen(filename) - strlen(extension) - 1);
}

/* ------------------------------------------------------------------------- */

const char* get_filename_extension(const char* path)
{
    const char* extension = get_last_substring_by_delimiter(path, '.');
    return extension;
}

/* ------------------------------------------------------------------------- */

bool check_file_exists(const char* path)
{
    FILE* fp;
    if((fp = fopen(path, "rb")) != NULL)
    {
        fclose(fp);
        return true;
    }

    return false;
}
