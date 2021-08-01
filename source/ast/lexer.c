#include "../../include/ast/lexer.h"

#include "../../include/utils/predefs.h"
#include "../../include/utils/string.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LEXER_PREFIX "LexicalAnalysis"

/* ------------------------------------------------------------------------- */

/* Checks whether token is a comment or not. */
static
bool is_token_comment(const char* p_string) {
    return p_string[0] == ';';
}

/* Checks whether token is an opcode or not. */
static
bool is_token_opcode(const char* p_string) {
    return get_opcode_from_string(p_string) != OPCODE_UNKNOWN;
}

/* Checks whether token is a label or not. */
static
bool is_token_label(const char* p_string) {
    return get_label_from_string(p_string) != LABEL_UNKNOWN;
}

/* Checks whether token is an optional label or not. */
static
bool is_token_optional_label(const char* p_string) {
    return p_string[strlen(p_string) - 1] == ':';
}

/* ------------------------------------------------------------------------- */

static
size_t count_spaces_and_commas(const char* string, size_t length)
{
    size_t i;
    size_t result = 0;

    for(i = 0; i < length; i++)
        result += (isspace(string[i]) || string[i] == ',');

    return result;
}

static
char** split_line_string(const char* string, size_t length)
{
    char** tokens;
    size_t array_index;
    size_t begin, end;

    begin       = 0;
    array_index = 0;
    tokens      = (char*)malloc(count_spaces_and_commas(string, length) * sizeof(char*));

    for(end = 0; end < length; end++)
    {
        if(isspace(string[end]) || string[end] == ',')
        {
            tokens[array_index] = strncpy(string, begin, end);
            array_index++;
            begin = end;
        }
    }

    return tokens;
}

/* ------------------------------------------------------------------------- */
LexerTokens lexer_tokenize_line(const char* string, size_t line)
{
    size_t length, i;
    const char** tokens;

#ifndef NDEBUG
    printf("[%s] Parsing: '%s' at line: %d\n", LEXER_PREFIX, string, line);
#endif

    length = strlen(string);
    tokens = split_line_string(string, length);

    for(i = 0; i < count_spaces_and_commas(string, length); i++)
        printf("%s", tokens[i]);
}
