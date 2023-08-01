#include <stdlib.h>

#define MAX_FILE_PATH_LENGTH        256

typedef struct vm_args_t {
    char *asm_file_path;
} vm_args_t;

void parse_args(int count, char** args, vm_args_t *parsed_args);