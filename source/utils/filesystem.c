#include "../../include/utils/filesystem.h"
#include "../../include/utils/string.h"
#include "../../include/utils/predefs.h"

#ifdef PLATFORM_WINDOWS
static const char path_slash = '\\';
#else
static const char path_slash = '/';
#endif

/* ------------------------------------------------------------------------- */

char* get_filename_from_path(char* path)
{
    const char* extension = get_last_substring_by_delimiter(path, '.');
    char* filename        = get_last_substring_by_delimiter(path, path_slash);
    
    if(extension == path)
        return filename;

    return get_substring(filename, 0, strlen(filename) - strlen(extension) - 1);
}
