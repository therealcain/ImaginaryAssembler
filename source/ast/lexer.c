#include "ast/lexer.h"
#include "utils/debug_print.h"
#include "utils/predefs.h"
#include "utils/string_utils.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEXER_PREFIX "LexicalAnalysis"

/* ------------------------------------------------------------------------- */

/* Allocating memory for LexerTokens. */
static
LexerTokens* make_lexer_tokens( size_t size )
{
    LexerTokens* tokens = (LexerTokens*)malloc( sizeof( LexerTokens ) );
    tokens->size        = size;
    tokens->p_tokens    = (LexerTokenVariant*)malloc( tokens->size * sizeof( LexerTokenVariant ) );

    return tokens;
}
/* ------------------------------------------------------------------------- */

/* Checks whether token is a comment or not. */
static
bool is_token_comment( const char* string )
{
    return string[ 0 ] == ';';
}

/* Checks whether token is an opcode or not. */
static
bool is_token_opcode( const char* string )
{
    return get_opcode_info_from_str( string ) != NULL;
}

/* Checks whether token is a label or not. */
static
bool is_token_label( const char* string )
{
    return get_label_info_from_str( string ) != NULL;
}

/* Checks whether token is an optional label or not. */
static
bool is_token_optional_label( const char* string )
{
    return string[ strlen( string ) - 1 ] == ':';
}

/* ------------------------------------------------------------------------- */

/* Skipping all of the spaces or commas until finding a character. */
static
size_t find_first_character( const char* string, size_t idx, size_t length )
{
    while( idx < length )
    {
        if( !(isspace( string[ idx ] ) || string[ idx ] == ',') )
            break;

        idx++;
    }

    return idx;
}
/* ------------------------------------------------------------------------- */

/* Skipping all characters until finding space or comma. In case of string it does not
   skip the space or commas. */
static
size_t find_first_space_or_comma( const char* string, size_t idx, size_t length )
{
    bool inside_quotation = false;

    while( idx < length )
    {
        if( isspace( string[ idx ] ) || string[ idx ] == ',' )
        {
            if( !inside_quotation )
                break;
        }

        if( string[ idx ] == '"' )
            inside_quotation = !inside_quotation;

        idx++;
    }

    return idx;
}
/* ------------------------------------------------------------------------- */

/* Fetching a token on every call.*/
static
char* get_next_token( const char* string, size_t* begin, size_t* end, size_t length )
{
    char* token;

    *begin = find_first_character( string, *begin, length );
    *end   = find_first_space_or_comma( string, *begin, length );

    token  = get_substring( string, *begin, *end );
    *begin = *end;

    return token;
}

/* ------------------------------------------------------------------------- */

/* Extracting the number of tokens in a string. */
static
size_t get_number_of_tokens( const char* string, size_t length )
{
    size_t begin, end;
    size_t counter;

    begin = end = counter = 0;

    while( end < length )
    {
        begin = find_first_character( string, begin, length );
        end   = find_first_space_or_comma( string, begin, length );
        begin = end;

        counter++;
    }

    return counter - 1;
}

/* ------------------------------------------------------------------------- */

LexerTokens* lexer_tokenize_line( const char* string, uint32_t line )
{
    LexerTokens* tokens;
    size_t tokens_idx;
    size_t length;
    size_t begin, end;
    size_t num_of_tokens;
    char* token;

    begin = end = tokens_idx = 0;

    length        = strlen( string );
    num_of_tokens = get_number_of_tokens( string, length );
    tokens        = make_lexer_tokens( num_of_tokens );

    debug_print( LOG_WARNING, "[%s] Parsing Line: %ld, \n\tTokens: %ld\n\tContent: %s\n",
        LEXER_PREFIX, line, num_of_tokens, string );

    while( (token = get_next_token( string, &begin, &end, length )) != NULL )
    {
        if( is_token_comment( token ) )
        {
            tokens->size = tokens_idx;

            free( (void*)token );
            break;
        }
        else
        {
            if( is_token_optional_label( token ) )
            {
                tokens->p_tokens[ tokens_idx ].type   = TOKEN_optional_label;

                token[ strlen( token ) - 1 ] = '\0';
                tokens->p_tokens[ tokens_idx ].p_data = (void*)token;
            }

            else if( is_token_label( token ) )
            {
                tokens->p_tokens[ tokens_idx ].type   = TOKEN_label;
                tokens->p_tokens[ tokens_idx ].p_data = (void*)get_label_info_from_str( token )->label;

                free( (void*)token );
            }

            else if( is_token_opcode( token ) )
            {
                tokens->p_tokens[ tokens_idx ].type   = TOKEN_opcode;
                tokens->p_tokens[ tokens_idx ].p_data = (void*)get_opcode_info_from_str( token )->opcode;

                free( (void*)token );
            }

            else
            {
                tokens->p_tokens[ tokens_idx ].type   = TOKEN_parameter;
                tokens->p_tokens[ tokens_idx ].p_data = (void*)token;
            }
        }

        tokens_idx++;
    }

    return tokens;
}

/* ------------------------------------------------------------------------- */

void lexer_tokens_clear( LexerTokens* p_tokens )
{
    size_t i;
    assert( p_tokens );

    for( i = 0; i < p_tokens->size; i++ )
    {
        LexerTokenTypes type = p_tokens->p_tokens[ i ].type;

        if( type == TOKEN_optional_label || type == TOKEN_parameter )
        {
            free( (void*)p_tokens->p_tokens[ i ].p_data );
            p_tokens->p_tokens[ i ].p_data = NULL;
        }
    }

    free( (void*)p_tokens->p_tokens );
    p_tokens->p_tokens = NULL;

    free( (void*)p_tokens );
    p_tokens = NULL;

}
