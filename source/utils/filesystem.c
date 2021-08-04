#include "../../include/utils/filesystem.h"
#include "../../include/utils/string.h"

#ifdef _WIN32
static const char path_slash = '\\';
#else
static const char path_slash = '/';
#endif

char* get_filename_from_path(char* path)
{
    char* filename_with_extension = get_last_substring_by_delimiter(path, path_slash);
    /* TODO: THIS */
}