#include "args.h"

void parse_args(int count, char** args, vm_args_t *parsed_args){
    if(count > 1){
        parsed_args->asm_file_path = args[1];
    }
}