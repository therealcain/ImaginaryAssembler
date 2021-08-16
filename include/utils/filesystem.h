#ifndef FILESYSTEM_GUARD_H
#define FILESYSTEM_GUARD_H

#include "my_bool.h"

#ifdef __cplusplus
extern "C" {
#endif

    /* Extracting the filename without extension. */
    char* get_filename_without_extension_from_path( const char* path );

    /* Extracting the extension from the filename. */
    const char* get_filename_extension( const char* path );

    /* Checking if a file in a given path exists. */
    bool can_read_file( const char* path );

#ifdef __cplusplus
}
#endif

#endif /* FILESYSTEM_GUARD_H */
