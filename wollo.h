#ifndef WOLLO
#define WOLLO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

const *char[] keywords = {
	"red",
	"green",
	"blue"
};

int isLetter(const char c);
char* getModifier(const char *piece, int *offset, const int len);
char* validateFormat(const char *format);
void print(const char *format, ...);

#endif