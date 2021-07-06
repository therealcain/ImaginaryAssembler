#include "../../include/ast/lexer.h"

#include "../../include/utils/predefs.h"
#include "../../include/utils/string.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LEXER_PREFIX "[LexicalAnalysis]"

/* ------------------------------------------------------------------------- */

/* Checks whether token is a comment or not. */
static
bool is_token_comment(const char* string) {
    return string[0] == ';';
}

/* Checks whether token is an opcode or not. */
static
bool is_token_opcode(const char* string) {
    return get_opcode_from_string(string) != OPCODE_UNKNOWN;
}

/* Checks whether token is a label or not. */
static
bool is_token_label(const char* string) {
    return get_label_from_string(string) != LABEL_UNKNOWN;
}

/* Checks whether token is an optional label or not. */
static
bool is_token_optional_label(const char* string) {
    return string[strlen(string) - 1] == ':';
}

/* ------------------------------------------------------------------------- */

/* Split string into tokens. */
static
const char* get_token(const char* string, size_t length, uint32_t* index)
{
    char* temp;
    size_t i;

    for(i = *index; i < length; ++i)
    {
        if(isspace(string[i]) || string[i] == ',')
            break;
    }

    temp = get_substring(string, *index, i);
    *index = i + 1;

    return temp;
}

/*
static
size_t get_number_of_tokens(const char* string, size_t length)
{
    size_t counter = 0;
    uint32_t index = 0;

    while(index < length)
    {
        UNUSED(get_token(string, length, &index));
        counter++;
    }

    return counter;
}
*/

/* ------------------------------------------------------------------------- */

static
void handle_opcode_token(LexerTokens* tokens, 
                         uint32_t* index, size_t length,
                         OpcodeTypes opcode)
{
     
}

static
void handle_label_token(LexerTokens* tokens, 
                        uint32_t* index, size_t length,
                        LabelTypes label)
{

}

static
void handle_optional_label_token(LexerTokens* tokens,
                                 uint32_t* index, size_t length,
                                 const char* label)
{

}

/* ------------------------------------------------------------------------- */

LexerTokens lexer_tokenize_line(const char* string, size_t line)
{
    LexerTokens tokens;

    uint32_t index  = 0;
    size_t   length = strlen(string);

    const char* token = get_token(string, length, &index);

    if(token != NULL)
    {
        if(!is_token_comment(token))
        {
            if(is_token_opcode(token))
                handle_opcode_token(&tokens, &index, length, get_opcode_from_string(token));

            else if(is_token_label(token))
                handle_label_token(&tokens, &index, length, get_label_from_string(token));

            else if(is_token_optional_label(token))
                handle_optional_label_token(&tokens, &index, length, token);
        }

        free((char*)token);
    }
    
    return tokens;
}

