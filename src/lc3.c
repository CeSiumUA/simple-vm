#include "lc3.h"

#define OP_DEF(operation)                           static void operation(uint16_t instruction)
#define TRP_DEF(operation)                          static void operation(void)

#define GET_OFFSET_MASK(instruction, offset, mask)  (((instruction) >> (offset)) & (mask))              
#define GET_R(instruction, register_offset)         GET_OFFSET_MASK(instruction, register_offset, LC3_R_MASK)
#define GET_SR(instruction)                         GET_R((instruction), (LC3_SR_OFFSET))
#define GET_DR(instruction)                         GET_R((instruction), (LC3_DR_OFFSET)) 
#define GET_CF(instruction)                         GET_DR((instruction))

#define GET_FLAG(instruction, offset)               GET_OFFSET_MASK(instruction, offset, (0x1))

bool lc3_running = false;

static uint16_t sign_extend(uint16_t ins, int bit_count);
static void update_cond_flag(uint16_t reg);

OP_DEF(add);
OP_DEF(ldi);
OP_DEF(and);
OP_DEF(not);
OP_DEF(branch);
OP_DEF(jump);
OP_DEF(jsr);
OP_DEF(ld);
OP_DEF(ldr);
OP_DEF(lea);
OP_DEF(st);
OP_DEF(sti);
OP_DEF(str);
OP_DEF(trap);

TRP_DEF(puts_lc3);
TRP_DEF(getc_lc3);
TRP_DEF(out_lc3);
TRP_DEF(in_lc3);
TRP_DEF(putsp_lc3);
TRP_DEF(halt_lc3);

static uint16_t memory_read(uint16_t address);

void lc3_reset(void){
    memset(memory, 0, sizeof(memory));
    memset(registers, 0, sizeof(registers));
    registers[R_COND] = FL_ZRO;

    registers[R_PC] = LC3_PC_DEFAULT_START;
}

void lc3_run(void){
    lc3_running = true;

    while (lc3_running)
    {
        uint16_t instruction = memory_read(registers[R_PC]++);

        uint16_t op = instruction >> 12;

        switch (op)
        {
            case OP_ADD:
                add(instruction);
                break;
            case OP_AND:
                and(instruction);
                break;
            case OP_NOT:
                not(instruction);
                break;
            case OP_BR:
                branch(instruction);
                break;
            case OP_JMP:
                jump(instruction);
                break;
            case OP_JSR:
                jsr(instruction);
                break;
            case OP_LD:
                ld(instruction);
                break;
            case OP_LDI:
                ldi(instruction);
                break;
            case OP_LDR:
                ldr(instruction);
                break;
            case OP_LEA:
                lea(instruction);
                break;
            case OP_ST:
                st(instruction);
                break;
            case OP_STI:
                sti(instruction);
                break;
            case OP_STR:
                str(instruction);
                break;
            case OP_TRAP:
                trap(instruction);
                break;
            case OP_RES:
            case OP_RTI:
            default:
                abort();
                break;
        }
    }
    
}

static uint16_t sign_extend(uint16_t ins, int bit_count){
    if((ins >> (bit_count - 1)) & 1){
        ins |= (0xFFFF << bit_count);
    }

    return ins;
}

static void update_cond_flag(uint16_t reg){
    if(registers[reg] == 0){
        registers[R_COND] = FL_ZRO;
    }
    else if(registers[reg] >> 15){
        registers[R_COND] = FL_NEG;
    }
    else{
        registers[R_COND] = FL_POS;
    }
}

static void add(uint16_t instruction){
    uint16_t dr = GET_DR(instruction);

    uint16_t sr1 = GET_SR(instruction);

    uint16_t imm_flag = GET_FLAG(instruction, LC3_ADD_IMM_FLAG_OFFSET);

    if(imm_flag){
        uint16_t imm_val = sign_extend(instruction & LC3_ADD_IMM_MASK, LC3_ADD_IMM_FLAG_OFFSET);
        registers[dr] = registers[sr1] + imm_val;
    }
    else{
        uint16_t sr2 = instruction & LC3_ADD_R_MASK;
        registers[dr] = registers[sr1] + registers[sr2];
    }

    update_cond_flag(dr);
}

static void ldi(uint16_t instruction){
    uint16_t dr = GET_DR(instruction);

    uint16_t pc_offset = lc3_sign_extend(instruction & LC3_LDI_ADDR_MASK, LC3_LDI_ADDR_LENGTH);

    uint16_t mem_ptr = memory_read(registers[R_PC] + pc_offset);

    registers[dr] = memory_read(mem_ptr);
}

static uint16_t memory_read(uint16_t address){
    return memory[address];
}

static void and(uint16_t instruction){
    uint16_t dr = GET_DR(instruction);

    uint16_t sr1 = GET_SR(instruction);

    uint16_t imm_flag = GET_FLAG(instruction, LC3_AND_IMM_FLAG_OFFSET);

    if(imm_flag){
        uint16_t imm_val = sign_extend(instruction & LC3_AND_IMM_MASK, LC3_AND_IMM_FLAG_OFFSET);

        registers[dr] = registers[sr1] & imm_val;
    }
    else{
        uint16_t sr2 = instruction & LC3_AND_R_MASK;

        registers[dr] = registers[sr1] & registers[sr2];
    }

    update_cond_flag(dr);
}

static void not(uint16_t instrcution){
    uint16_t dr = GET_DR(instrcution);

    uint16_t sr = GET_SR(instrcution);

    registers[dr] = ~registers[sr];

    update_cond_flag(dr);
}

static void branch(uint16_t instruction){
    uint16_t pc_offset = sign_extend(instruction & LC3_ADDR_MASK, LC3_ADDR_LENGTH);

    uint16_t cond_flag = GET_CF(instruction);

    if(cond_flag & registers[R_COND]){
        registers[R_PC] += pc_offset;
    }
}

static void jump(uint16_t instruction){
    uint16_t sr = GET_SR(instruction);
    registers[R_PC] = registers[sr];
}

static void jsr(uint16_t instruction){
    uint16_t long_flag = GET_FLAG(instruction, LC3_JSR_LONG_FLAG_OFFSET);

    registers[R_R7] = registers[R_PC];

    if(long_flag){
        uint16_t long_pc_offset = sign_extend(instruction & LC3_JSR_PC_MASK, LC3_JSR_LONG_FLAG_OFFSET);
        registers[R_PC] += long_pc_offset;
    }
    else{
        uint16_t sr = GET_SR(instruction);
        registers[R_PC] = registers[sr];
    }
}

static void ld(uint16_t instruction){
    uint16_t dr = GET_DR(instruction);

    uint16_t pc_offset = sign_extend(instruction & LC3_ADDR_MASK, LC3_ADDR_LENGTH);
    registers[dr] = memory_read(registers[R_PC] + pc_offset);

    update_cond_flag(dr);
}

static void ldr(uint16_t instruction){
    uint16_t dr = GET_DR(instruction);

    uint16_t offset = sign_extend(instruction & LC3_LDR_ADDR_MASK, LC3_LDR_ADDR_LENGTH);

    uint16_t sr = GET_SR(instruction);

    registers[dr] = memory_read(registers[sr] + offset);

    update_cond_flag(instruction);
}

static void lea(uint16_t instruction){
    uint16_t dr = GET_DR(instruction);

    uint16_t pc_offset = sign_extend(instruction & LC3_LEA_ADDR_MASK, LC3_LEA_ADDR_LENGTH);

    registers[dr] = registers[R_PC] + pc_offset;

    update_cond_flag(dr);
}

static void st(uint16_t instruction){
    uint16_t dr = GET_DR(instruction);

    uint16_t pc_offset = sign_extend(instruction & LC3_ST_ADDR_MASK, LC3_ST_ADDR_LENGTH);

    memory[(registers[R_PC] + pc_offset)] = registers[dr];
}

static void sti(uint16_t instruction){
    uint16_t dr = GET_DR(instruction);

    uint16_t pc_offset = sign_extend(instruction & LC3_STI_ADDR_MASK, LC3_STI_ADDR_LENGTH);

    uint16_t ptr_addr = memory_read(registers[R_PC] + pc_offset);

    memory[ptr_addr] = registers[dr];
}

static void str(uint16_t instruction){
    uint16_t dr = GET_DR(instruction);

    uint16_t sr = GET_SR(instruction);

    uint16_t pc_offset = sign_extend(instruction & LC3_STR_ADDR_MASK, LC3_STR_ADDR_LENGTH);

    uint16_t base_addr = registers[sr];

    memory[base_addr + pc_offset] = registers[dr];
}

static void trap(uint16_t instruction){
    registers[R_R7] = registers[R_PC];

    switch (instruction & 0xFF)
    {
        case TRAP_GETC:
            getc_lc3();
            break;
        case TRAP_OUT:
            out_lc3();
            break;
        case TRAP_PUTS:
            puts_lc3();
            break;
        case TRAP_IN:
            in_lc3();
            break;
        case TRAP_PUTSP:
            putsp_lc3();
            break;
        case TRAP_HALT:
            halt_lc3();
            break;
    }
}

static void puts_lc3(void){
    uint16_t *c = memory + registers[R_R0];

    while (*c)
    {
        putc((char *)c, stdout);
        c++;
    }
    fflush(stdout);
}

static void getc_lc3(void){
    registers[R_R0] = (uint16_t)getchar();
    update_cond_flag(R_R0);
}

static void out_lc3(void){
    char c = (char)registers[R_R0];

    putc(c, stdout);

    fflush(stdout);
}

static void in_lc3(void){
    printf("Enter a character: ");

    char c = getchar();
    putc(c, stdout);

    fflush(stdout);

    registers[R_R0] = (uint16_t)c;

    update_cond_flag(R_R0);
}

static void putsp_lc3(void){
    uint16_t *c = memory + registers[R_R0];

    while(*c){
        char c1 = (*c) & 0xFF;
        putc(c1, stdout);
        char c2 = (*c) >> 8;
        if(c2){
            putc(c2, stdout);
        }

        c++;
    }

    fflush(stdout);
}

static void halt_lc3(void){
    puts("HALT");
    fflush(stdout);
    lc3_running = false;
}