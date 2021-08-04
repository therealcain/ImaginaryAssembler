#include "../../include/ast/parser.h"
#include "../../include/utils/debug_logger.h"
#include "../../include/opcodes.h"

#include <stdio.h>

#define PARSER_PREFIX "ParserAnalysis"

/* Counting type of the tokens. */
static
size_t count_lexer_tokens_enums(const LexerTokens* p_tokens, LexerTokenTypes type)
{
    size_t count;
    size_t i;

    count = 0;

    for(i = 0; i < p_tokens->size; i++)
        count += p_tokens->p_tokens[i].type == type;

    return count;
}

static size_t count_parameters     (const LexerTokens* p_tokens) { return count_lexer_tokens_enums(p_tokens, TOKEN_parameter);      }
static size_t count_labels         (const LexerTokens* p_tokens) { return count_lexer_tokens_enums(p_tokens, TOKEN_label);          }
static size_t count_optional_labels(const LexerTokens* p_tokens) { return count_lexer_tokens_enums(p_tokens, TOKEN_optional_label); }
static size_t count_opcodes        (const LexerTokens* p_tokens) { return count_lexer_tokens_enums(p_tokens, TOKEN_opcode);         }

/* ------------------------------------------------------------------------- */

static
OpcodeTypes get_opcode_from_lexer(const LexerTokens* p_tokens)
{
    size_t i;
    for(i = 0; i < p_tokens->size; i++)
    {
        if(p_tokens->p_tokens[i].type == TOKEN_opcode)
            return (OpcodeTypes)p_tokens->p_tokens[i].data.venum;
    }

    return OPCODE_UNKNOWN;
}

/* ------------------------------------------------------------------------- */

/* Making sure tokens are valid. */
static
bool validate_line(const LexerTokens* p_tokens, size_t line)
{
    size_t labels, optional_labels, opcodes, parameters; 

    labels          = count_labels(p_tokens);
    optional_labels = count_optional_labels(p_tokens);
    opcodes         = count_opcodes(p_tokens);
    parameters      = count_parameters(p_tokens);

    /* Making sure there aren't too many labels. */
    if(labels >= 2)
    {
        debug_log(LOG_ERROR, "Error:\n");
        fprintf(stderr, "[%s] [Line: %ld] Too many labels!\n", PARSER_PREFIX, line);
        return false;
    }
    
    /* Making sure there aren't too many optional labels. */
    if(optional_labels >= 2)
    {
        debug_log(LOG_ERROR, "Error:\n");
        fprintf(stderr, "[%s] [Line: %ld] Too many optional labels!\n", PARSER_PREFIX, line);
        return false;
    }

    /* Making sure there aren't too many opcodes. */
    if(opcodes >= 2)
    {
        debug_log(LOG_ERROR, "Error:\n");
        fprintf(stderr, "[%s] [Line: %ld] Too many operation codes!\n", PARSER_PREFIX, line);
        return false;
    }

    /* Making sure there aren't label and opcodes together. */
    if(opcodes >= 1 && labels >= 1)
    {
        debug_log(LOG_ERROR, "Error:\n");
        fprintf(stderr, "[%s] [Line: %ld] You can't mix operation codes and labels!\n", PARSER_PREFIX, line);
        return false;
    }

    /* Making sure there there is at least an opcode and a label. */
    if(opcodes == 0 && labels == 0)
    {
        debug_log(LOG_ERROR, "Error:\n");
        fprintf(stderr, "[%s] [Line: %ld] Unknown command.\n", PARSER_PREFIX, line);
        return false;
    }

    /* Making sure opcode number of parameters are valid. */
    if(opcodes == 1)
    {
        const OpcodeTypes type       = get_opcode_from_lexer(p_tokens);
        const int8_t expected_params = opcode_expect_number_of_params(type);

        if((int8_t)parameters != expected_params)
        {
            debug_log(LOG_ERROR, "Error:\n");

            if((int8_t)parameters < expected_params)
                fprintf(stderr, "[%s] [Line: %ld] opcode parameters are too little.\n", PARSER_PREFIX, line);
            else
                fprintf(stderr, "[%s] [Line: %ld] opcode parameters are too many.\n", PARSER_PREFIX, line);

            return false;
        }
    }

    return true;
}

/* ------------------------------------------------------------------------- */

// static
// void generate_symbol_table(LexerTokens* p_tokens)
// {
    
// }

/* ------------------------------------------------------------------------- */

bool parser_parse_line(const LexerTokens* p_tokens, size_t line)
{
    if(validate_line(p_tokens, line))
    {
        // generate_symbol_table(p_tokens);
        debug_log(LOG_WARNING, "[%s] success on line %ld\n", PARSER_PREFIX, line);

        return true;
    }

    return false;
}
