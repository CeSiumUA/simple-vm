#include "lc3.h"

bool lc3_running = false;

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
        uint16_t pc_address = (registers[R_PC]++);
        uint16_t instruction = memory[pc_address];

        uint16_t op = instruction >> 12;

        switch (op)
        {
            case OP_ADD:
                @{ADD}
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
                @{LDI}
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