#ifndef FILESYSTEM_GUARD_H
#define FILESYSTEM_GUARD_H

#include "stdbool.h"

/* Extracting the filename without extension. */
char* get_filename_without_extension_from_path(const char* path);

/* Extracting the extension from the filename. */
const char* get_filename_extension(const char* path);

/* Checking if a file in a given path exists. */
bool check_file_exists(const char* path);

#endif /* FILESYSTEM_GUARD_H */
