#include "../include/assembler.h"
#include "../include/ast/lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include "../include/utils/stdint.h"

void start_assembler(const char* path)
{
#define BUFFER_SIZE 81

    FILE*    fp = NULL;
    char     buf[BUFFER_SIZE];
    uint32_t line = 1;

    fp = fopen(path, "r");

    /* Making sure path actually exists. */
    if(fp == NULL)
    {
        fprintf(stderr, "Failed to load: %s, Skipping...", path);
        return;
    }

    /* Fetching every line. */
    while(fgets(buf, BUFFER_SIZE, fp)) 
    {
        const LexerTokens tokens = lexer_tokenize_line(buf, line);
        /* printf("%s", buf); */

        line++;
    }

    fclose(fp);
}

