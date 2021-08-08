#include "../include/assembler.h"
#include "../include/ast/lexer.h"
#include "../include/ast/parser.h"

#include <stdio.h>
#include <stdlib.h>
#include "../include/utils/filesystem.h"
#include "../include/utils/stdint.h"
#include "../include/utils/string.h"
#include "../include/utils/vector.h"

#define ASSEMBLER_PREFIX "Assembler"
#define BUFFER_SIZE 81

/* ------------------------------------------------------------------------- */

static
void overwrite_file(const char *filename, const char* extension)
{
    char buf[64] = "\0";

    buffer_concentrate_string(buf, BUFFER_SIZE, filename, extension);

    if(check_file_exists(buf))
    {
        printf("[%s] Overwriting file: %s\n", ASSEMBLER_PREFIX, buf);
        remove(buf);
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
    FILE*         fp;
    char          buf[BUFFER_SIZE];
    uint32_t      line = 1;
    const char*   filename;
    bool          parse_success = true;
    GenericVector all_tokens;
    size_t        i;

    if(strcmp(get_filename_extension(path), "as") != 0)
    {
        fprintf(stderr, "[%s] Make sure file extension is .as!", ASSEMBLER_PREFIX);
        return;
    }

    fp = fopen(path, "r");

    if(fp == NULL)
    {
        fprintf(stderr, "Failed to load: %s, Skipping...", path);
        return;
    }

    filename = get_filename_without_extension_from_path(path);

    check_existence_output_files(filename);
    all_tokens = construct_vector();

    printf("[%s] Reading file: %s\n", ASSEMBLER_PREFIX, path);

    while(fgets(buf, BUFFER_SIZE, fp)) 
    {
        LexerTokens* tokens = lexer_tokenize_line(buf, line); /* Heap Allocate*/
        vector_push_back(&all_tokens, (void*)tokens);

        /* Line is not empty. */
        if(tokens->size != 0)
        {
            if(!parser_validate_line(tokens, line))
                parse_success = false;
        }

        line++;
    }
    
    if(parse_success)
        printf("[%s] Validation finished successfully.\n", ASSEMBLER_PREFIX);

    /* Cleanup */
    printf("[%s] Performing cleanup.\n", ASSEMBLER_PREFIX);
    for(i = 0; i < vector_size(&all_tokens); i++)
    {
        LexerTokens* p_token = (LexerTokens*)vector_at(&all_tokens, i);
        lexer_tokens_clear(p_token);
    }

    vector_clear(&all_tokens);
    free((void*)filename);
    fclose(fp);
}
