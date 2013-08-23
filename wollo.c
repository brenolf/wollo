#include "wollo.h"

static char nextToken(){
	return 'x';
}

void print(const char *format, ...){
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	printf("%c\n", nextToken());
}

#define nextToken NULL