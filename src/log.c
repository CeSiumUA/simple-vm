#include "log.h"

#define PRINT_VA(S)    va_list va;\
                    va_start(va, (S));\
                    vprintf((S), va);\
                    va_end(va)

#define PRINT_NEW_LINE  printf("\r\n")

void log_printn(const char *str, ...){
    PRINT_VA(str);
    PRINT_NEW_LINE;
}

void log_print(const char *str, ...){
    PRINT_VA(str);
}

void debug_print(const char *str, ...){
    #ifdef DEBUG_MODE
    PRINT_VA(str);
    #endif
}

void debug_printn(const char *str, ...){
    #ifdef DEBUG_MODE
    PRINT_VA(str);
    PRINT_NEW_LINE;
    #endif
}