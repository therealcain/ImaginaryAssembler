#ifndef PARSER_GUARD_H
#define PARSER_GUARD_H

#include "lexer.h"

#include "../utils/stdbool.h"
#include "../utils/stdint.h"

extern bool parser_validate_line(const LexerTokens* p_tokens, uint32_t line, const char* filename);

#endif /* PARSER_GUARD_H */
