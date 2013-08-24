#ifndef WOLLO
#define WOLLO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

char* getModifier(const char *piece);
char* validateFormat(const char *format);
void print(const char *format, ...);

#endif