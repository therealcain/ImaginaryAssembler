#include "../include/opcodes.h"

#include "../include/utils/stdint.h"
#include <string.h>

typedef struct { 
    char*       name; 
    OpcodeTypes opcode; 
} HashOpcode;

static const HashOpcode lookup_table[] = {
    { "add" , OPCODE_add  },
    { "sub" , OPCODE_sub  },
    { "and" , OPCODE_and  },
    { "or"  , OPCODE_or   },
    { "nor" , OPCODE_nor  },
    { "move", OPCODE_move },
    { "mvhi", OPCODE_mvhi },
    { "mvlo", OPCODE_mvlo },
    { "addi", OPCODE_addi },
    { "subi", OPCODE_subi },
    { "andi", OPCODE_andi },
    { "ori" , OPCODE_ori  },
    { "nori", OPCODE_nori },
    { "bne" , OPCODE_bne  },
    { "blt" , OPCODE_blt  },
    { "bgt" , OPCODE_bgt  },
    { "lb"  , OPCODE_lb   },
    { "sb"  , OPCODE_sb   },
    { "lw"  , OPCODE_lw   },
    { "sw"  , OPCODE_sw   },
    { "lh"  , OPCODE_lh   },
    { "sh"  , OPCODE_sh   },
    { "jmp" , OPCODE_jmp  },
    { "la"  , OPCODE_la   },
    { "call", OPCODE_call },
    { "stop", OPCODE_stop }
};

static const size_t lookup_table_size = sizeof(lookup_table) / sizeof(HashOpcode);

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