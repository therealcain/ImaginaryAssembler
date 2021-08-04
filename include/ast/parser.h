#ifndef PARSER_GUARD_H
#define PARSER_GUARD_H

#include "lexer.h"

#include "../utils/stdbool.h"
#include "../utils/stdint.h"

extern bool parser_parse_line(const LexerTokens* p_tokens, size_t line);

#endif /* PARSER_GUARD_H */
