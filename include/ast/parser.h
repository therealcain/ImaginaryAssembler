#ifndef PARSER_GUARD_H
#define PARSER_GUARD_H

#include "lexer.h"

#include "../utils/my_bool.h"
#include "../utils/my_inttypes.h"
#include "../utils/my_vector.h"

/* Looking for parsing errors. */
extern bool parser_validate_line( const LexerTokens* p_tokens, uint32_t line );

/* Generating files: file.ob, file.ent, file.ext. */
extern void parser_parse( const GenericVector* p_all_tokens, const char* filename );

#endif /* PARSER_GUARD_H */
