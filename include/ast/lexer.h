#ifndef LEXER_GUARD_H
#define LEXER_GUARD_H

#include "../utils/my_bool.h"
#include "../utils/my_inttypes.h"
#include "../opcodes.h"
#include "../labels.h"

typedef enum {
    TOKEN_label = 0,
    TOKEN_optional_label,
    TOKEN_opcode,
    TOKEN_parameter
} LexerTokenTypes;

typedef struct {
    LexerTokenTypes type;
    void* p_data;
} LexerTokenVariant;

typedef struct {
    LexerTokenVariant* p_tokens;
    size_t             size;
} LexerTokens;

/* Tokenizing the entire line. */
extern LexerTokens* lexer_tokenize_line( const char* string, uint32_t line );

/* Cleaning internals. */
extern void lexer_tokens_clear( LexerTokens* p_tokens );

/* Printing all of the tokens in the tokens array. */
extern void print_tokens( LexerTokens* p_tokens );

/* Counting the number of tokens in the tokens array. */
extern size_t count_lexer_tokens( const LexerTokens* p_tokens, LexerTokenTypes type );
#define count_lexer_parameters(tokens) count_lexer_tokens(tokens, TOKEN_parameter)
#define count_lexer_labels(tokens) count_lexer_tokens(tokens, TOKEN_label)
#define count_lexer_optional_labels(tokens) count_lexer_tokens(tokens, TOKEN_optional_label)
#define count_lexer_opcodes(tokens) count_lexer_tokens(tokens, TOKEN_opcode)

#endif /* LEXER_GUARD_H */

