#include "wollo.h"

int isLetter(const char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char* getModifier(const char *piece, int *offset, const int len){
	int i = *offset + 1;

	if(i == len)
		return NULL;

	char *tag = (char*) malloc(sizeof(format) * len);
	int j = 0;

	for(; i < len && piece[i] != '>' && piece[i + 1] != '>'; i++){
		tag[j++] = piece[i];
	}

	if(i == len){
		free(tag);
		return NULL;
	}

	return NULL;
}

char* validateFormat(const char *format){
	int i = 0, j = 0, dif = 0, len = strlen(format);
	char *nf = (char*) malloc(sizeof(format) * len);
	char *st = (char*) malloc(sizeof(format) * len);
	char c_pos, *find;

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
			if(st = getModifier(format, &i, len)){
				free(nf);
				errno = EINVAL;
				perror("There is no matching '>'");
				return NULL;
			}

			strcat(nf, st);
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

//#define isLetter NULL
//#define validateFormat NULL
//#define getModifier NULL