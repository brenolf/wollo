#ifndef WOLLO
#define WOLLO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern const char *wollo_tags[][3];

int get_tag (char *tag);
char* tokenize (char *haystack, char **needles, int n_needles, int *chosen, char **next);
int interpret (const char *format, char **target);
void print (const char *format, ...);

#endif
