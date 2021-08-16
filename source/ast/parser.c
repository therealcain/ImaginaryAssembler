#include "ast/parser.h"
#include "utils/debug_print.h"
#include "opcodes.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PARSER_PREFIX "ParserAnalysis"

/* Counting type of the tokens. */
static
size_t count_lexer_tokens_enums( const LexerTokens* p_tokens, LexerTokenTypes type )
{
    size_t count;
    size_t i;

    count = 0;

    for( i = 0; i < p_tokens->size; i++ )
        count += p_tokens->p_tokens[ i ].type == type;

    return count;
}

static
size_t count_parameters( const LexerTokens* p_tokens )
{
    return count_lexer_tokens_enums( p_tokens, TOKEN_parameter );
}

static
size_t count_labels( const LexerTokens* p_tokens )
{
    return count_lexer_tokens_enums( p_tokens, TOKEN_label );
}

static
size_t count_optional_labels( const LexerTokens* p_tokens )
{
    return count_lexer_tokens_enums( p_tokens, TOKEN_optional_label );
}

static
size_t count_opcodes( const LexerTokens* p_tokens )
{
    return count_lexer_tokens_enums( p_tokens, TOKEN_opcode );
}

/* ------------------------------------------------------------------------- */

static
OpcodeTypes get_opcode_from_lexer( const LexerTokens* p_tokens )
{
    size_t i;
    for( i = 0; i < p_tokens->size; i++ )
    {
        if( p_tokens->p_tokens[ i ].type == TOKEN_opcode )
            return (OpcodeTypes)p_tokens->p_tokens[ i ].p_data;
    }

    return OPCODE_UNKNOWN;
}

/* ------------------------------------------------------------------------- */

/* Making sure tokens are valid. Returning true on success. */
static
bool validate_line( const LexerTokens* p_tokens, uint32_t line )
{
    /*
     * INValid CASES:
     *  1. Labels >= 2
     *  2. Optional Labels >= 2
     *  3. Opcodes >= 2
     *  4. Opcodes >= 1 and Labels >= 1
     *  5. Opcodes == 0 and Labels == 0
     *  6. Opcodes == 1 --> Parameters...
     *  7. Labels == 1 --> Parameters == 0
     */
    size_t labels, optional_labels, opcodes, parameters;

    labels          = count_labels( p_tokens );
    optional_labels = count_optional_labels( p_tokens );
    opcodes         = count_opcodes( p_tokens );
    parameters      = count_parameters( p_tokens );

    /* Making sure there aren't too many labels. */
    if( labels >= 2 )
    {
        debug_print( LOG_ERROR, "Error:\n" );
        fprintf( stderr, "[%s] [Line: %d] Too many labels!\n", PARSER_PREFIX, line );
        return false;
    }

    /* Making sure there aren't too many optional labels. */
    if( optional_labels >= 2 )
    {
        debug_print( LOG_ERROR, "Error:\n" );
        fprintf( stderr, "[%s] [Line: %d] Too many optional labels!\n", PARSER_PREFIX, line );
        return false;
    }

    /* Making sure there aren't too many opcodes. */
    if( opcodes >= 2 )
    {
        debug_print( LOG_ERROR, "Error:\n" );
        fprintf( stderr, "[%s] [Line: %d] Too many operation codes!\n", PARSER_PREFIX, line );
        return false;
    }

    /* Making sure there aren't label and opcodes together. */
    if( opcodes >= 1 && labels >= 1 )
    {
        debug_print( LOG_ERROR, "Error:\n" );
        fprintf( stderr, "[%s] [Line: %d] You can't mix operation codes and labels!\n", PARSER_PREFIX, line );
        return false;
    }

    /* Making sure there there is at least an opcode and a label. */
    if( opcodes == 0 && labels == 0 )
    {
        debug_print( LOG_ERROR, "Error:\n" );
        fprintf( stderr, "[%s] [Line: %d] Specify an operation code or label!\n", PARSER_PREFIX, line );
        return false;
    }

    /* Making sure opcode number of parameters are valid. */
    if( opcodes == 1 )
    {
        const OpcodeTypes type       = get_opcode_from_lexer( p_tokens );
        const int8_t expected_params = get_opcode_info_from_opcode( type )->expected_params;

        if( (int8_t)parameters != expected_params )
        {
            debug_print( LOG_ERROR, "Error:\n" );

            if( (int8_t)parameters < expected_params )
                fprintf( stderr, "[%s] [Line: %d] Opcode parameters are too little.\n", PARSER_PREFIX, line );
            else
                fprintf( stderr, "[%s] [Line: %d] Opcode parameters are too many.\n", PARSER_PREFIX, line );

            return false;
        }
    }

    /* Making sure labels have parameters. */
    if( labels == 1 && parameters == 0 )
    {
        debug_print( LOG_ERROR, "Error:\n" );
        fprintf( stderr, "[%s] [Line: %d] Label is expecting parameters.", PARSER_PREFIX, line );
        return false;
    }

    return true;
}

/* ------------------------------------------------------------------------- */

/* Making sure all tokens are parameters after index. Returning true if finished successfully. */
static
bool check_parameters_starting_from_index( const LexerTokens* p_tokens, uint32_t line, size_t index )
{
    for( ; index < p_tokens->size; index++ )
    {
        if( p_tokens->p_tokens[ index ].type != TOKEN_parameter )
        {
            debug_print( LOG_ERROR, "Error:\n" );
            fprintf( stderr, "[%s] [Line: %d] Your parameter at position %ld is invalid!\n", PARSER_PREFIX, line, index );
            return false;
        }
    }

    return true;
}

/* Making sure lines have the correct order of sequences. */
static
bool validate_line_sequence( const LexerTokens* p_tokens, uint32_t line )
{
    /*
     * Valid CASES:
     *  1. Optional Label --> Label  --> Parameters...
     *  2. Optional Label --> Opcode --> Parameters...
     *  3. Opcode --> Parameters...
     *  4. Label --> Parameters...
     */

    if( p_tokens->size >= 1 )
    {
        LexerTokenTypes type = p_tokens->p_tokens[ 0 ].type;

        if( type == TOKEN_optional_label )
        {
            if( p_tokens->size >= 2 )
            {
                type = p_tokens->p_tokens[ 1 ].type;


                if( type == TOKEN_label || type == TOKEN_opcode )
                    return check_parameters_starting_from_index( p_tokens, line, 2 );
                else
                {
                    debug_print( LOG_ERROR, "Error:\n" );
                    fprintf( stderr, "[%s] [Line: %d] Second parameter is invalid! make sure it's either an opcode or label.\n", PARSER_PREFIX, line );
                }
            }
        }
        else if( type == TOKEN_opcode || type == TOKEN_label )
            return check_parameters_starting_from_index( p_tokens, line, 1 );

        else if( type == TOKEN_parameter )
        {
            debug_print( LOG_ERROR, "Error:\n" );
            fprintf( stderr, "[%s] [Line: %d] Cannot start with a parameter!\n", PARSER_PREFIX, line );
        }
    }

    return false;
}

/* ------------------------------------------------------------------------- */

bool parser_validate_line( const LexerTokens* p_tokens, uint32_t line )
{
    if( validate_line( p_tokens, line ) && validate_line_sequence( p_tokens, line ) )
    {
        debug_print( LOG_WARNING, "[%s] success on line %ld\n", PARSER_PREFIX, line );

        return true;
    }

    return false;
}

/* ------------------------------------------------------------------------- */

typedef enum {
    SYMBOL_TABLE_ATTRIBUTES_code,
    SYMBOL_TABLE_ATTRIBUTES_data,
    SYMBOL_TABLE_ATTRIBUTES_external,
    SYMBOL_TABLE_ATTRIBUTES_entry
} SymbolTableAttributes;

typedef struct {
    const char* p_symbol;
    uint32_t              value;
    uint32_t              address;
    SymbolTableAttributes attr1, attr2;
} RowSymbolTable;

static
GenericVector* generate_symbol_table( const GenericVector* p_all_tokens, const char* filename )
{
    static const uint32_t StartingAddress = 100;
    static const uint32_t AddressSize     = 4;

    size_t i;
    uint32_t address = StartingAddress;

    GenericVector* stvec = allocate_vector();

    for( i = 0; i < vector_size( p_all_tokens ); i++ )
    {
        const LexerTokenVariant* p_tokens = ((LexerTokens*)vector_at( (GenericVector*)p_all_tokens, i ))->p_tokens;

        if( p_tokens[ 0 ].type == TOKEN_optional_label || p_tokens[ 0 ].type == TOKEN_label )
        {
            RowSymbolTable* p_table = (RowSymbolTable*)malloc( sizeof( RowSymbolTable ) );

            if( p_tokens[ 0 ].type == TOKEN_optional_label )
            {
                p_table->address  = address;
                p_table->p_symbol = (const char*)p_tokens[ 0 ].p_data;

                if( p_tokens[ 1 ].type == TOKEN_opcode )
                    p_table->attr1 = SYMBOL_TABLE_ATTRIBUTES_code;
                else if( p_tokens[ 1 ].type == TOKEN_label )
                    p_table->attr1 = SYMBOL_TABLE_ATTRIBUTES_data;
            }
            else
            {
                LabelTypes type = (LabelTypes)p_tokens[ 0 ].p_data;

                if( type == LABEL_entry )
                {
                    p_table->address       = address;
                    p_table->attr1 = SYMBOL_TABLE_ATTRIBUTES_entry;
                    p_table->p_symbol      = (const char*)p_tokens[ 1 ].p_data;
                }
                else if( type == LABEL_extern )
                {
                    p_table->address       = address;
                    p_table->attr1 = SYMBOL_TABLE_ATTRIBUTES_external;
                    p_table->p_symbol      = (const char*)p_tokens[ 1 ].p_data;
                }
            }

            vector_push_back( stvec, (void*)p_table );
        }

        address += AddressSize;
    }

    return stvec;
}

static
void merge_symbol_table( GenericVector* p_vec )
{
    size_t i, j;
    size_t len = vector_size( p_vec );

    for( i = 0; i < len; i++ )
    {
        for( j = 0; j < len; j++ )
        {
            if( i != j )
            {
                RowSymbolTable* ivec = (RowSymbolTable*)vector_at( p_vec, i );
                RowSymbolTable* jvec = (RowSymbolTable*)vector_at( p_vec, j );

                if( ivec->p_symbol != NULL && jvec->p_symbol != NULL )
                {
                    if( strcmp( ivec->p_symbol, jvec->p_symbol ) == 0 )
                    {
                        ivec->attr2 = jvec->attr1;
                        vector_remove_by_ptr( p_vec, jvec );
                        len = vector_size( p_vec );
                    }
                }
            }
        }
    }
}

static
void debug_print_symbol_table( const GenericVector* p_vec )
{
#ifndef NDEBUG
    size_t i;
    for( i = 0; i < vector_size( p_vec ); i++ )
    {
        const RowSymbolTable* table = (RowSymbolTable*)vector_at( (GenericVector*)p_vec, i );
        debug_print( LOG_NORMAL, "[%s] Symbol: %s, Value: %u, Address: %u, Attributes: %u, %u\n",
            PARSER_PREFIX, table->p_symbol, table->value, table->address, (uint8_t)table->attr1, (uint8_t)table->attr2 );
    }
#endif
}

/* ------------------------------------------------------------------------- */

void parser_parse( const GenericVector* p_all_tokens, const char* filename )
{
    GenericVector* st = generate_symbol_table( p_all_tokens, filename );
    merge_symbol_table( st );
    debug_print_symbol_table( st );

    // clear_symbol_table(p_st);
}
