#ifndef LC3_H_
#define LC3_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LC3_MEMORY_MAX                  (1 << 16)
#define LC3_PC_DEFAULT_START            (0x3000)

#define LC3_ADD_DR_OFFSET               (9)
#define LC3_ADD_R_MASK                  (0x7)
#define LC3_ADD_SR_OFFSET               (6)                 
#define LC3_ADD_IMM_FLAG_OFFSET         (5)
#define LC3_ADD_IMM_MASK                (0x1F)

#define LC3_LDI_DR_OFFSET               LC3_ADD_DR_OFFSET
#define LC3_LDI_R_MASK                  LC3_ADD_R_MASK
#define LC3_LDI_ADDR_MASK               (0x1FF)
#define LC3_LDI_ADDR_LENGTH             LC3_LDI_DR_OFFSET

typedef enum LC3_REGISTER
{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,
    R_COND,
    R_COUNT
} LC3_REGISTER;

typedef enum LC3_OPCODE
{
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */
} LC3_OPCODE;

typedef enum LC3_COND_FLAG
{
    FL_POS = 1 << 0, /* P */
    FL_ZRO = 1 << 1, /* Z */
    FL_NEG = 1 << 2, /* N */
} LC3_COND_FLAG;

uint16_t memory[LC3_MEMORY_MAX];
uint16_t registers[R_COUNT];

void lc3_reset(void);
void lc3_run(void);

#endif