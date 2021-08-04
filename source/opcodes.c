#include "../include/opcodes.h"

#include "../include/utils/stdint.h"
#include <string.h>

typedef struct { 
    char*       name; 
    OpcodeTypes opcode;
    int8_t      expected_params;
} HashOpcode;

static const HashOpcode lookup_table[] = {
    { "add" , OPCODE_add , 3 },
    { "sub" , OPCODE_sub , 3 },
    { "and" , OPCODE_and , 3 },
    { "or"  , OPCODE_or  , 3 },
    { "nor" , OPCODE_nor , 3 },
    { "move", OPCODE_move, 2 },
    { "mvhi", OPCODE_mvhi, 2 },
    { "mvlo", OPCODE_mvlo, 2 },
    { "addi", OPCODE_addi, 3 },
    { "subi", OPCODE_subi, 3 },
    { "andi", OPCODE_andi, 3 },
    { "ori" , OPCODE_ori , 3 },
    { "nori", OPCODE_nori, 3 },
    { "bne" , OPCODE_bne , 3 },
    { "blt" , OPCODE_blt , 3 },
    { "bgt" , OPCODE_bgt , 3 },
    { "lb"  , OPCODE_lb  , 3 },
    { "sb"  , OPCODE_sb  , 3 },
    { "lw"  , OPCODE_lw  , 3 },
    { "sw"  , OPCODE_sw  , 3 },
    { "lh"  , OPCODE_lh  , 3 },
    { "sh"  , OPCODE_sh  , 3 },
    { "jmp" , OPCODE_jmp , 1 },
    { "la"  , OPCODE_la  , 1 },
    { "call", OPCODE_call, 1 },
    { "stop", OPCODE_stop, 0 }
};

static const size_t lookup_table_size = sizeof(lookup_table) / sizeof(HashOpcode);

/* ------------------------------------------------------------------------- */

OpcodeTypes get_opcode_from_string(const char* string)
{
    size_t i;
    for(i = 0; i < lookup_table_size; ++i)
    {
        const HashOpcode* lookup = &lookup_table[i];

        if(strcmp(lookup->name, string) == 0)
            return lookup->opcode;
    }

    return OPCODE_UNKNOWN;
}

/* ------------------------------------------------------------------------- */

const char* get_string_from_opcode(OpcodeTypes type)
{
    size_t i;
    for(i = 0; i < lookup_table_size; ++i)
    {
        const HashOpcode* lookup = &lookup_table[i];

        if(type == lookup->opcode)
            return lookup->name;
    }

    return NULL;
}

/* ------------------------------------------------------------------------- */

int8_t opcode_expect_number_of_params(OpcodeTypes type)
{
    size_t i;
    for(i = 0; i < lookup_table_size; ++i)
    {
        const HashOpcode* lookup = &lookup_table[i];

        if(type == lookup->opcode)
            return lookup->expected_params;
    }

    return -1;
}
