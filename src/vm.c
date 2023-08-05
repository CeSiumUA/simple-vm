#include "vm.h"

vm_result start_vm(vm_args_t vm_args){
    FILE *asm_file = fopen(vm_args.asm_file_path, 'r');

    if(asm_file == NULL){
        debug_printn("ASM file not found by specified path: %s", vm_args.asm_file_path);
        return ASM_FILE_NOT_FOUND;
    }

    lc3_reset();
}