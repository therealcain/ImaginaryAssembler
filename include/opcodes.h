#ifndef OPCODES_GUARD_H
#define OPCODES_GUARD_H

typedef enum {

    OPCODE_add = 0,
    OPCODE_sub    ,
    OPCODE_and    ,
    OPCODE_or     ,
    OPCODE_nor    ,
    OPCODE_move   ,
    OPCODE_mvhi   ,
    OPCODE_mvlo   ,
    OPCODE_addi   ,
    OPCODE_subi   ,
    OPCODE_andi   ,
    OPCODE_ori    ,
    OPCODE_nori   ,
    OPCODE_bne    ,
    OPCODE_beq    ,
    OPCODE_blt    ,
    OPCODE_bgt    ,
    OPCODE_lb     ,
    OPCODE_sb     ,
    OPCODE_lw     ,
    OPCODE_sw     ,
    OPCODE_lh     ,
    OPCODE_sh     ,
    OPCODE_jmp    ,
    OPCODE_la     ,
    OPCODE_call   ,
    OPCODE_stop   ,
    OPCODE_UNKNOWN

} OpcodeTypes;

/* A hash function to convert string to opcode. */
extern OpcodeTypes get_opcode_from_string(const char* string);

/* A hash function to convert opcode to string. */
extern const char* get_string_from_opcode(OpcodeTypes type);

#endif /* OPCODES_GUARD_H */

