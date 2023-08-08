#ifndef LOG_H_
#define LOG_H_

#include "main.h"
#include <stdio.h>
#include <stdarg.h>

void log_printn(const char *str, ...);
void log_print(const char *str, ...);
void debug_print(const char *str, ...);
void debug_printn(const char *str, ...);

#endif