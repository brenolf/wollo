#ifndef WOLLO
#define WOLLO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>

extern const char *colours[];

char* taggify(char *tag, char *index);
char* interpret(const char *format, int len);
int validateFormat(const char *format, char **target);
void print(const char *format, ...);

#endif