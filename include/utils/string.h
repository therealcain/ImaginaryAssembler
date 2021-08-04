#ifndef STRING_GUARD_H
#define STRING_GUARD_H

#include "stdint.h"
#include <string.h>

/* Creates new string with malloc and copy characters. */
char* get_substring(const char* string, size_t begin, size_t end);

/* Locate last delimiter. */
char* get_last_substring_by_delimiter(char* string, char delimiter);

#endif /* STRING_GUARD_H */

