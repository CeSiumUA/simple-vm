#include "lc3.h"

void lc3_reset(void){
    memset(memory, 0, sizeof(memory));
    memset(registers, 0, sizeof(registers));
    registers[R_COND] = FL_ZRO;

    registers[R_PC] = LC3_PC_DEFAULT_START;
}