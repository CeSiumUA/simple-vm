#ifndef VM_H_
#define VM_H_

#include "log.h"
#include "args.h"
#include <stdio.h>
#include <stdlib.h>

#include "lc3.h"

typedef enum VM_EXIT_CODE {
    OK = 0,
    ASM_FILE_NOT_FOUND,
    INVALID_INSTRUCTION,
} VM_EXIT_CODE;

typedef VM_EXIT_CODE vm_result;

vm_result start_vm(vm_args_t vm_args);

#endif