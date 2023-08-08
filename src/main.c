#include "main.h"

int main(int argc, char **argv){
    vm_args_t vm_args;

    printf("Welcome to LC-3 vm!\r\n");

    #ifdef DEBUG_MODE
    printf("Provided arguments:\r\n");
    for(int i = 0; i < argc; i++){
        printf("\t%s\r\n", argv[i]);
    }
    #endif

    signal(SIGINT, stop_vm);

    parse_args(argc, argv, &vm_args);

    start_vm(vm_args);

    return 0;
}