#ifndef LC3_H_
#define LC3_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

#define LC3_MEMORY_MAX                  (1 << 16)
#define LC3_PC_DEFAULT_START            (0x3000)

#define LC3_DR_OFFSET                   (9)
#define LC3_R_MASK                      (0x7)
#define LC3_SR_OFFSET                   (6)
#define LC3_IMM_FLAG_OFFSET             (5)
#define LC3_IMM_MASK                    (0x1F)
#define LC3_ADDR_MASK                   (0x1FF)
#define LC3_ADDR_LENGTH                 (9)

#define LC3_ADD_DR_OFFSET               LC3_DR_OFFSET
#define LC3_ADD_R_MASK                  LC3_R_MASK
#define LC3_ADD_SR_OFFSET               LC3_SR_OFFSET                 
#define LC3_ADD_IMM_FLAG_OFFSET         LC3_IMM_FLAG_OFFSET
#define LC3_ADD_IMM_MASK                LC3_IMM_MASK

#define LC3_LDI_DR_OFFSET               LC3_ADD_DR_OFFSET
#define LC3_LDI_R_MASK                  LC3_ADD_R_MASK
#define LC3_LDI_ADDR_MASK               LC3_ADDR_MASK
#define LC3_LDI_ADDR_LENGTH             LC3_ADDR_LENGTH

#define LC3_AND_DR_OFFSET               LC3_ADD_DR_OFFSET
#define LC3_AND_R_MASK                  LC3_ADD_R_MASK
#define LC3_AND_SR_OFFSET               LC3_ADD_SR_OFFSET
#define LC3_AND_IMM_FLAG_OFFSET         LC3_ADD_IMM_FLAG_OFFSET
#define LC3_AND_IMM_MASK                LC3_ADD_IMM_MASK

#define LC3_NOT_DR_OFFSET               LC3_ADD_DR_OFFSET
#define LC3_NOT_R_MASK                  LC3_ADD_R_MASK
#define LC3_NOT_SR_OFFSET               LC3_ADD_SR_OFFSET

#define LC3_JSR_LONG_FLAG_OFFSET        (11)
#define LC3_JSR_SR_OFFSET               LC3_SR_OFFSET
#define LC3_JSR_PC_MASK                 (0x7FF)

#define LC3_LDR_ADDR_LENGTH             (6)
#define LC3_LDR_ADDR_MASK               (0x3F)

#define LC3_LEA_ADDR_MASK               LC3_ADDR_MASK
#define LC3_LEA_ADDR_LENGTH             LC3_ADDR_LENGTH

#define LC3_ST_ADDR_MASK                LC3_ADDR_MASK
#define LC3_ST_ADDR_LENGTH              LC3_ADDR_LENGTH

#define LC3_STI_ADDR_MASK               LC3_ADDR_MASK
#define LC3_STI_ADDR_LENGTH             LC3_ADDR_LENGTH

#define LC3_STR_ADDR_LENGTH             LC3_LDR_ADDR_LENGTH
#define LC3_STR_ADDR_MASK               LC3_LDR_ADDR_MASK

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

typedef enum LC3_TRAP_CODE{
    TRAP_GETC = 0x20,  /* get character from keyboard, not echoed onto the terminal */
    TRAP_OUT = 0x21,   /* output a character */
    TRAP_PUTS = 0x22,  /* output a word string */
    TRAP_IN = 0x23,    /* get character from keyboard, echoed onto the terminal */
    TRAP_PUTSP = 0x24, /* output a byte string */
    TRAP_HALT = 0x25   /* halt the program */
} LC3_TRAP_CODE;

typedef enum LC3_COND_FLAG
{
    FL_POS = 1 << 0, /* P */
    FL_ZRO = 1 << 1, /* Z */
    FL_NEG = 1 << 2, /* N */
} LC3_COND_FLAG;

typedef enum LC3_MMR{
    MR_KBSR = 0xFE00, /* keyboard status */
    MR_KBDR = 0xFE02  /* keyboard data */
} LC3_MMR;

void lc3_reset(void);
void lc3_run(void);
void lc3_load_image(FILE *file);
void lc3_stop(void);

#endif