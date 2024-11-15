#ifndef STRING_UTILS_GUARD_H
#define STRING_UTILS_GUARD_H

#include "inttypes.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

    /* Creates new string with malloc and copy characters. */
    extern char* get_substring( const char* string, size_t begin, size_t end );

    /* Locate last delimiter. */
    extern const char* get_last_substring_by_delimiter( const char* string, char delimiter );

    /* Concentrate two strings into a different buffer. */
    extern void buffer_concatenate_string( char* dest, size_t len, const char* src1, const char* src2 );

    /* Creating and copying a string. */
    extern char* copy_string( const char* string );

    /* Changing string to lower. */
    extern void string_tolower( char* string );

#ifdef __cplusplus
}
#endif

#endif /* STRING_UTILS_GUARD_H */

