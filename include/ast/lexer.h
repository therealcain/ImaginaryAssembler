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

#endif /* LEXER_GUARD_H */

