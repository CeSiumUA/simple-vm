#include "lc3.h"

bool lc3_running = false;

static uint16_t sign_extend(uint16_t ins, int bit_count);
static void update_cond_flag(uint16_t reg);
static void add(uint16_t instruction);
static void ldi(uint16_t instruction);
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
                @{AND}
                break;
            case OP_NOT:
                @{NOT}
                break;
            case OP_BR:
                @{BR}
                break;
            case OP_JMP:
                @{JMP}
                break;
            case OP_JSR:
                @{JSR}
                break;
            case OP_LD:
                @{LD}
                break;
            case OP_LDI:
                ldi(instruction);
                break;
            case OP_LDR:
                @{LDR}
                break;
            case OP_LEA:
                @{LEA}
                break;
            case OP_ST:
                @{ST}
                break;
            case OP_STI:
                @{STI}
                break;
            case OP_STR:
                @{STR}
                break;
            case OP_TRAP:
                @{TRAP}
                break;
            case OP_RES:
            case OP_RTI:
            default:
                @{BAD OPCODE}
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
    uint16_t dr = (instruction >> LC3_ADD_DR_OFFSET) & LC3_ADD_R_MASK;

    uint16_t sr1 = (instruction >> LC3_ADD_SR_OFFSET) & LC3_ADD_R_MASK;

    uint16_t imm_flag = (instruction >> LC3_ADD_IMM_FLAG_OFFSET) & 0x1;

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
    uint16_t dr = (instruction >> LC3_LDI_DR_OFFSET) & LC3_LDI_R_MASK;

    uint16_t pc_offset = lc3_sign_extend(instruction & LC3_LDI_ADDR_MASK, LC3_LDI_ADDR_LENGTH);

    uint16_t mem_ptr = memory_read(registers[R_PC] + pc_offset);

    registers[dr] = memory_read(mem_ptr);
}

static uint16_t memory_read(uint16_t address){
    return memory[address];
}