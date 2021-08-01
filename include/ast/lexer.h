#ifndef LEXER_GUARD_H
#define LEXER_GUARD_H

#include "../utils/stdbool.h"
#include "../utils/stdint.h"
#include "../opcodes.h"
#include "../labels.h"

typedef enum {
    TOKEN_label = 0     ,
    TOKEN_optional_label,
    TOKEN_opcode        ,
    TOKEN_parameter
} LexerTokenTypes;

typedef struct {
    LexerTokenTypes types;
    void*           p_data;
} LexerTokenVariant;

typedef struct {
    LexerTokenVariant* p_tokens;
    size_t             size;

    const char* p_error;
} LexerTokens;

extern LexerTokens lexer_tokenize_line(const char* string, size_t line);

#endif /* LEXER_GUARD_H */

