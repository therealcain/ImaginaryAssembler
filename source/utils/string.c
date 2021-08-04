#include "../../include/utils/string.h"

#include <stdlib.h>

char* get_substring(const char* string, size_t begin, size_t end)
{
    int32_t size;
    char* substr;

    size = end - begin;

    if(size <= 0)
        return NULL;

    substr = (char*)malloc(size + 1);
    if(substr == NULL)
        return NULL;

    strncpy(substr, string + begin, size);
    substr[size] = '\0';

    return substr;
}

/* ------------------------------------------------------------------------- */

char* get_last_substring_by_delimiter(char* string, char delimiter)
{
    char* ret = strrchr(string, delimiter);

    if(ret == NULL)
        ret = string;
    else 
        ret++;

    return ret;
}