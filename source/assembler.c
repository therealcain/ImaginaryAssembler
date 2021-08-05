#include "../include/assembler.h"
#include "../include/ast/lexer.h"
#include "../include/ast/parser.h"

#include <stdio.h>
#include <stdlib.h>
#include "../include/utils/filesystem.h"
#include "../include/utils/stdint.h"

void start_assembler(const char* path)
{
#define BUFFER_SIZE 81

    FILE*       fp = NULL;
    char        buf[BUFFER_SIZE];
    uint32_t    line = 1;
    const char* filename;

    fp = fopen(path, "r");

    if(fp == NULL)
    {
        fprintf(stderr, "Failed to load: %s, Skipping...", path);
        return;
    }

    filename = get_filename_from_path(path);

    while(fgets(buf, BUFFER_SIZE, fp)) 
    {
        /* TODO: NOT FORGET CLEANUP. */
        const LexerTokens tokens = lexer_tokenize_line(buf, line);

        /* Line is not empty. */
        if(tokens.size != 0)
        {
            parser_parse_line(&tokens, line);
            
        }

        line++;
    }

    free((void*)filename);
    fclose(fp);
}

