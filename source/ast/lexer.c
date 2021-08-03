#include "../../include/ast/lexer.h"
#include "../../include/utils/debug_logger.h"

#include "../../include/utils/predefs.h"
#include "../../include/utils/string.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define LEXER_PREFIX "LexicalAnalysis"

/* ------------------------------------------------------------------------- */

/* Allocating memory for LexerTokens. */
static
LexerTokens make_lexer_tokens(size_t size)
{
    LexerTokens tokens;
    tokens.size    = size;
    tokens.p_tokens = (LexerTokenVariant*)malloc(tokens.size * sizeof(LexerTokenVariant));

    return tokens;
}
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

/* Skipping all of the spaces or commas until finding a character. */
static
size_t find_first_character(const char* string, size_t idx, size_t length)
{
    while(idx < length)
    {
        if( !(isspace(string[idx]) || string[idx] == ',') )
            break;
        
        idx++;
    }

    return idx;
}
/* ------------------------------------------------------------------------- */

/* Skipping all characters until finding space or comma. In case of string it does not
   skip the space or commas. */
static
size_t find_first_space_or_comma(const char* string, size_t idx, size_t length)
{
    bool inside_quotation = false;

    while(idx < length)
    {
        if(isspace(string[idx]) || string[idx] == ',')
        {
            if(!inside_quotation)
                break;
        }

        if(string[idx] == '"')
            inside_quotation = !inside_quotation;

        idx++;
    }

    return idx;
}
/* ------------------------------------------------------------------------- */

/* Fetching a token on every call.*/
static
const char* get_next_token(const char* string, size_t* begin, size_t* end, size_t length)
{
    const char* token;

    *begin = find_first_character(string, *begin, length);
    *end   = find_first_space_or_comma(string, *begin, length);

    token  = get_substring(string, *begin, *end);
    *begin = *end;

    return token;
}

/* ------------------------------------------------------------------------- */

/* Extracting the number of tokens in a string. */
static
size_t get_number_of_tokens(const char* string, size_t length)
{
    size_t begin, end;
    size_t counter;

    begin = end = counter = 0;

    while(end < length)
    {
        begin = find_first_character(string, begin, length);
        end   = find_first_space_or_comma(string, begin, length);
        begin = end;

        counter++;
    }

    return counter - 1;
}

/* ------------------------------------------------------------------------- */
static
void print_tokens(LexerTokens* p_tokens)
{
    size_t i;

    assert(p_tokens);

    for(i = 0; i < p_tokens->size; i++)
    {
        switch(p_tokens->p_tokens[i].type)
        {
        case TOKEN_label:
            debug_log(LOG_NORMAL, "Label: %s\n", 
                get_string_from_label((LabelTypes)p_tokens->p_tokens[i].data.venum));
            break;

        case TOKEN_optional_label:
            debug_log(LOG_NORMAL, "Optional Label: %s\n", 
                p_tokens->p_tokens[i].data.string);
            break;

        case TOKEN_opcode:
            debug_log(LOG_NORMAL, "Opcode: %s\n", 
                get_string_from_opcode((OpcodeTypes)p_tokens->p_tokens[i].data.venum));
            break;

        case TOKEN_parameter:
            debug_log(LOG_NORMAL, "Parameter: %s\n", 
                p_tokens->p_tokens[i].data.string);
            break;
        }
    }
}

/* ------------------------------------------------------------------------- */
LexerTokens lexer_tokenize_line(const char* string, size_t line)
{
    LexerTokens tokens;
    size_t tokens_idx;
    size_t length;
    size_t begin, end;
    size_t num_of_tokens;
    const char* token;

    begin = end = tokens_idx = 0;

    length        = strlen(string);
    num_of_tokens = get_number_of_tokens(string, length);
    tokens        = make_lexer_tokens(num_of_tokens);

    debug_log(LOG_WARNING, 
        "[%s] Parsing Line: %ld, \n\tTokens: %ld\n\tContent: %s\n", 
         LEXER_PREFIX, line, num_of_tokens, string);

    while((token = get_next_token(string, &begin, &end, length)) != NULL)
    {
        if(is_token_comment(token))
        {
            free((void*)token);
            return tokens;
        }
        else
        {
            if(is_token_optional_label(token))
            {
                tokens.p_tokens[tokens_idx].type        = TOKEN_optional_label;
                tokens.p_tokens[tokens_idx].data.string = token;
            }

            else if(is_token_label(token))
            {
                tokens.p_tokens[tokens_idx].type       = TOKEN_label;
                tokens.p_tokens[tokens_idx].data.venum = (uint8_t)get_label_from_string(token);
                
                free((void*)token);
            }

            else if(is_token_opcode(token))
            {
                tokens.p_tokens[tokens_idx].type        = TOKEN_opcode;
                tokens.p_tokens[tokens_idx].data.venum = (uint8_t)get_opcode_from_string(token);

                free((void*)token);
            }
            
            else
            {
                tokens.p_tokens[tokens_idx].type        = TOKEN_parameter;
                tokens.p_tokens[tokens_idx].data.string = token;
            }
        }

        tokens_idx++;
    }

#ifndef NDEBUG
    print_tokens(&tokens);
#endif

    return tokens;
}
