#include "opcodes.h"

#include "utils/my_inttypes.h"
#include <string.h>

static const OpcodeInfo lookup_table [] ={
    { "add" , OPCODE_add , 3, 4},
    { "sub" , OPCODE_sub , 3, 4},
    { "and" , OPCODE_and , 3, 4},
    { "or"  , OPCODE_or  , 3, 4},
    { "nor" , OPCODE_nor , 3, 4},
    { "move", OPCODE_move, 2, 4},
    { "mvhi", OPCODE_mvhi, 2, 4},
    { "mvlo", OPCODE_mvlo, 2, 4},
    { "addi", OPCODE_addi, 3, 4},
    { "subi", OPCODE_subi, 3, 4},
    { "andi", OPCODE_andi, 3, 4},
    { "ori" , OPCODE_ori , 3, 4},
    { "nori", OPCODE_nori, 3, 4},
    { "bne" , OPCODE_bne , 3, 4},
    { "blt" , OPCODE_blt , 3, 4},
    { "bgt" , OPCODE_bgt , 3, 4},
    { "lb"  , OPCODE_lb  , 3, 4},
    { "sb"  , OPCODE_sb  , 3, 4},
    { "lw"  , OPCODE_lw  , 3, 4},
    { "sw"  , OPCODE_sw  , 3, 4},
    { "lh"  , OPCODE_lh  , 3, 4},
    { "sh"  , OPCODE_sh  , 3, 4},
    { "jmp" , OPCODE_jmp , 1, 4},
    { "la"  , OPCODE_la  , 1, 4},
    { "call", OPCODE_call, 1, 4},
    { "stop", OPCODE_stop, 0, 4}
};

static const size_t lookup_table_size = sizeof( lookup_table ) / sizeof( OpcodeInfo );

/* ------------------------------------------------------------------------- */

const OpcodeInfo* get_opcode_info_from_str( const char* str )
{
    size_t i;
    for( i = 0; i < lookup_table_size; ++i )
    {
        const OpcodeInfo* lookup = &lookup_table[ i ];

        if( strcmp( lookup->name, str ) == 0 )
            return lookup;
    }

    return NULL;
}

/* ------------------------------------------------------------------------- */

const OpcodeInfo* get_opcode_info_from_opcode( OpcodeTypes type )
{
    size_t i;
    for( i = 0; i < lookup_table_size; ++i )
    {
        const OpcodeInfo* lookup = &lookup_table[ i ];

        if( type == lookup->opcode )
            return lookup;
    }

    return NULL;
}
