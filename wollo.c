#include "wollo.h"

char* getModifier(const char *piece){
	return NULL;
}

char* validateFormat(const char *format){
	int i = 0, j = 0, len = strlen(format);
	char *nf = (char*) malloc(sizeof(format) * len);
	char *st = (char*) malloc(sizeof(format) * len);
	char c_pos;

	for(; i < len; i++) {
		c_pos = format[i];

		if(c_pos != '<'){
			nf[j++] = c_pos;
			continue;
		}

		if(i + 1 == len){
			free(nf);
			errno = EINVAL;
			perror("There is no matching '>'");
			return NULL;
		}

		if(format[i + 1] == '<'){
			nf[j++] = '<';
			i++;
		} else {
			if(strchr(format + i, '>') == NULL || (st = getModifier(format + i)) == NULL){
				free(nf);
				errno = EINVAL;
				perror("There is no matching '>'");
				return NULL;
			}

			strcat(nf, st);
			i += strlen(st);
		}
	}

	nf[j] = '\0';
	return nf;
}

void print(const char *format, ...){
	char *nf = validateFormat(format);

	if(nf == NULL)
		return;

	va_list args;
	va_start(args, format);
	vprintf(nf, args);
	va_end(args);
}

#define validateFormat NULL
#define getModifier NULL