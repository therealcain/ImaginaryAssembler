#ifndef OPCODES_GUARD_H
#define OPCODES_GUARD_H

#include "utils/my_inttypes.h"

typedef enum {
    OPCODE_add = 0,
    OPCODE_sub,
    OPCODE_and,
    OPCODE_or,
    OPCODE_nor,
    OPCODE_move,
    OPCODE_mvhi,
    OPCODE_mvlo,
    OPCODE_addi,
    OPCODE_subi,
    OPCODE_andi,
    OPCODE_ori,
    OPCODE_nori,
    OPCODE_bne,
    OPCODE_beq,
    OPCODE_blt,
    OPCODE_bgt,
    OPCODE_lb,
    OPCODE_sb,
    OPCODE_lw,
    OPCODE_sw,
    OPCODE_lh,
    OPCODE_sh,
    OPCODE_jmp,
    OPCODE_la,
    OPCODE_call,
    OPCODE_stop,
    OPCODE_UNKNOWN
} OpcodeTypes;

/* ------------------------------------------------------------------------- */

typedef struct {
    const char* name;
    OpcodeTypes opcode;
    int8_t      expected_params;
} OpcodeInfo;

/* ------------------------------------------------------------------------- */

/* A function to retrieve the opcode info based on a string. */
extern const OpcodeInfo* get_opcode_info_from_str( const char* str );

/* A function to retrieve the opcode info based on a type. */
extern const OpcodeInfo* get_opcode_info_from_opcode( OpcodeTypes type );

#endif /* OPCODES_GUARD_H */

