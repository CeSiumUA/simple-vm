#ifndef VM_H_
#define VM_H_

#include "log.h"
#include "args.h"
#include "lc3.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

typedef enum VM_EXIT_CODE {
    VM_OK = 0,
    VM_ASM_FILE_NOT_FOUND,
    VM_INVALID_INSTRUCTION,
} VM_EXIT_CODE;

typedef VM_EXIT_CODE vm_result;

vm_result start_vm(vm_args_t vm_args);
void disable_input_buffering(void);
void restore_input_buffering(void);
void stop_vm(int signal);

#endif