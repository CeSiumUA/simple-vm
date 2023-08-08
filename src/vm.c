#include "vm.h"

struct termios original_tio;

vm_result start_vm(vm_args_t vm_args){

    FILE *asm_file = fopen(vm_args.asm_file_path, "rb");

    if(!asm_file){
        debug_printn("ASM file not found by specified path: %s", vm_args.asm_file_path);
        return ASM_FILE_NOT_FOUND;
    }

    disable_input_buffering();

    lc3_load_image(asm_file);

    fclose(asm_file);

    lc3_reset();

    lc3_run();

    restore_input_buffering();

    return OK;
}

void disable_input_buffering(void){
    tcgetattr(STDIN_FILENO, &original_tio);
    struct termios new_tio = original_tio;
    new_tio.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void restore_input_buffering(void){
    tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}

void stop_vm(int signal){
    lc3_stop();
    restore_input_buffering();

    debug_printn("exitting with signal: %d", signal);

    exit(-2);
}