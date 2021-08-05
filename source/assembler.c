#include "../include/assembler.h"
#include "../include/ast/lexer.h"
#include "../include/ast/parser.h"

#include <stdio.h>
#include <stdlib.h>
#include "../include/utils/filesystem.h"
#include "../include/utils/stdint.h"
#include "../include/utils/string.h"

#define ASSEMBLER_PREFIX "Assembler"
#define BUFFER_SIZE 81

/* ------------------------------------------------------------------------- */

static
void overwrite_file(const char *filename, const char* extension)
{
    char buf[BUFFER_SIZE] = "\0";

    buffer_concentrate_string(buf, BUFFER_SIZE, filename, extension);

    if(check_file_exists(buf))
    {
        printf("[%s] Overwriting file: %s\n", ASSEMBLER_PREFIX, filename);
        remove(filename);
    }
}

static 
void check_existence_output_files(const char* filename)
{
#ifndef NDEBUG
    /* .dst = Debug Symbol Table */
    overwrite_file(filename, ".dst");
#endif

    /* .ob = Object */
    overwrite_file(filename, ".ob");

    /* .ent = Entry */
    overwrite_file(filename, ".ent");

    /* .ext = External */
    overwrite_file(filename, ".ext");
}

/* ------------------------------------------------------------------------- */

void start_assembler(const char* path)
{
    FILE*       fp;
    char        buf[BUFFER_SIZE];
    uint32_t    line = 1;
    const char* filename;
    bool        parse_success = true;

    fp = fopen(path, "r");

    if(fp == NULL)
    {
        fprintf(stderr, "Failed to load: %s, Skipping...", path);
        return;
    }

    filename = get_filename_without_extension_from_path(path);

    check_existence_output_files(filename);

    printf("[%s] Reading file: %s\n", ASSEMBLER_PREFIX, path);

    while(fgets(buf, BUFFER_SIZE, fp)) 
    {
        /* TODO: NOT FORGET CLEANUP. */
        const LexerTokens tokens = lexer_tokenize_line(buf, line);

        /* Line is not empty. */
        if(tokens.size != 0)
        {
            if(!parser_validate_line(&tokens, line, filename))
                parse_success = false;
        }

        line++;
    }
    
    if(parse_success)
        printf("[%s] Validation finished successfully.\n", ASSEMBLER_PREFIX);

    free((void*)filename);
    fclose(fp);
}
