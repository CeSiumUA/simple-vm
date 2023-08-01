#include "args.h"

void parse_args(int count, char** args, vm_args_t *parsed_args){
    parsed_args->asm_file_path = args[0];
}