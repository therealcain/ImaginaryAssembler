#ifndef STRING_GUARD_H
#define STRING_GUARD_H

#include "stdint.h"
#include <string.h>

/* Creates new string with malloc and copy characters. */
char* get_substring(const char* string, size_t begin, size_t end);

/* Locate last delimiter. */
const char* get_last_substring_by_delimiter(const char* string, char delimiter);

/* Concentrate two strings into a different buffer. */
void buffer_concentrate_string(char* dest, size_t len, const char* src1, const char* src2);

/* Creating and copying a string. */
char* copy_string(const char* string);

#endif /* STRING_GUARD_H */

