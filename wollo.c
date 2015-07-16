#include "wollo.h"

const char *wollo_tags[][3] = {
  { NULL,  "\e[0m", ""},
  { "blink", "\e[5m", "\e[25m"},
  { "dim", "\e[2m", "\e[22m"},
  { "u", "\e[4m", "\e[24m"},
  { "inverted", "\e[7m", "\e[27m"},
  { "r", "\e[31m", "\e[39m"},
  { "g", "\e[32m", "\e[39m"},
  { "y", "\e[33m", "\e[39m"},
  { "b", "\e[34m", "\e[39m"},
  { "m", "\e[35m", "\e[39m"},
  { "c", "\e[36m", "\e[39m"}
};

int get_tag (char *tag) {
  int i;

  for (i = 1; i < 11; i++) {
    if (strcmp(wollo_tags[i][0], tag) == 0) {
      return i;
    }
  }

  return -1;
}

char* tokenize (char *haystack, char **needles, int n_needles, int *chosen, char **next) {
  if (haystack == NULL || n_needles == 0) {
    return NULL;
  }

  if (*next != NULL) {
    haystack = *next;
  }

  if (haystack[0] == '\0') {
    return NULL;
  }

  char *find = NULL;
  int i, j;

  for (i = 0; i < n_needles; i++) {
    char *local = strstr(haystack, needles[i]);

    if (find == NULL || (local != NULL && find > local)) {
      j = i;
      find = local;
    }
  }

  if (find == NULL) {
    *chosen = -1;
    *next = haystack + strlen(haystack);
  } else {
    *chosen = j;
    *next = find + strlen(needles[j]);
    *find = '\0';
  }

  return haystack;
}

int interpret (const char *format, char **target) {
  int length = strlen(format);

  int *stack = malloc(sizeof(int) * (length / 3));
  int peak = -1;

  char *aux = malloc(sizeof(char) * length);
  *target = malloc(sizeof(char) * length);

  strcpy(aux, format);
  strcpy(*target, "");

  char *string;
  char *delimiters[2] = {"<<", ">>"};
  char *token = NULL;
  int chosen;

  char *substring;
  char *subdelimiters[2] = {"<", ">"};
  char *subtoken = NULL;
  int subchosen;

  int count;
  int tag;

  while ((string = tokenize(aux, delimiters, 2, &chosen, &token)) != NULL) {
    subtoken = NULL;
    count = 0;

    while ((substring = tokenize(string, subdelimiters, 2,
      &subchosen, &subtoken)) != NULL) {

      if (count++ % 2 == 0)  {
        strcat(*target, substring);
      } else {
        int closing = (substring[0] == '/');
        tag = get_tag(substring + closing);

        if (closing) {
          if (tag == -1 || peak < 0) {
            fprintf(stderr, "print: Invalid closing tag `%s'.\n",
              substring + 1);
            exit(2);
          }

          if (stack[peak] != tag) {
            fprintf(stderr, "print: Invalid closing tag `%s', `%s' expected.\n",
               substring + 1, wollo_tags[stack[peak]][0]);
            exit(2);
          }

          strcat(*target, wollo_tags[tag][2]);

          peak--;
          tag = peak < 0 ? 0 : stack[peak];
        } else if (tag == -1) {
          fprintf(stderr, "print: Invalid tag `%s'.\n", substring);
          exit(2);
        } else {
          stack[++peak] = tag;
        }

        strcat(*target, wollo_tags[tag][1]);
      }
    }

    strcat(*target, chosen >= 0 ? delimiters[chosen] : "");
  }

  free(aux);

  if (peak >= 0) {
    fprintf(stderr, "print: Missing closing tag `%s'.\n",
      wollo_tags[stack[peak]][0]);
    exit(2);
  }

  return -1;
}

void print (const char *format, ...) {
  char *new = NULL;
  int err;

  interpret(format, &new);

  va_list args;

  va_start(args, format);
  vprintf(new, args);
  va_end(args);

  free(new);
}
