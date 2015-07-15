#include "wollo.h"

const char *colours[] = {"", "r", "g", "y", "b", "m", "c"};

char* taggify(char *tag, char *index) {
  char *new = (char*) malloc(sizeof(char) * 10);

  if (tag == NULL) {
    sprintf(new, "\x1b[m");
    return new;
  }

  int i;

  for(i = 1; i < 7; i++) {
    if(strcmp(colours[i], tag) == 0) {
      sprintf(new, "\x1b[3%dm", i);
      *index = i;
      return new;
    }
  }

  *index = -1;
  return NULL;
}

char* interpret(const char *format, int len) {
  int i = 0;
  char* read = (char*) malloc(sizeof(char) * len);

  while (format[i] != '\0' && format[i] != '>') {
    read[i] = format[i];
    i++;
  }

  read[i] = '\0';

  if (format[i] == '\0' || i == 0)
    return NULL;

  return read;
}

int validateFormat(const char *format, char **target) {
  char *new;
  char *content;
  char *tag;
  char *reset_tag;
  char index;

  int len;
  int init;
  int content_len;
  int tag_len;
  int reset_len;

  int cursor = 0, i, flag = 0;

  char *stack = (char*) malloc(sizeof(char) * len);
  int top = 0;

  len = strlen(format);
  init = len;
  new = (char*) malloc(sizeof(char) * len);

  reset_tag = taggify(NULL, NULL);
  reset_len = strlen(reset_tag);

  for(i = 0; i < init; i++) {
    flag = 0;

    if(format[i] == '<') {

      if (i + 1 == len)
        return i;

      if (format[i + 1] == '<') {
        new[cursor++] = '<';
        i++;
      } else {
        if (format[i + 1] == '/') {
          i++;
          flag = 1;
        }

        content = interpret(format + i + 1, len);

        if (content == NULL || (tag = taggify(content, &index)) == NULL) {
          free(new);
          return init - 1;
        }

        if (flag == 0) {
          tag_len = strlen(tag);
          content_len = strlen(content);

          new = (char*) realloc(new, sizeof(char) * len + tag_len);

          strcat(new, tag);

          i += (1 + content_len);
          len += tag_len;

          stack[top++] = index;
          cursor += tag_len;
        } else {
          content_len = strlen(content);

          new = (char*) realloc(new, sizeof(char) * len + reset_len);

          strcat(new, reset_tag);

          if (stack[--top] != index)
            return i;

          i += (1 + content_len);
          len += reset_len;
          cursor += reset_len;

          if (top > 0) {
            free(content);

            content = malloc(sizeof(char) * strlen(colours[stack[top - 1]]) + 1);
            strcpy(content, colours[stack[top - 1]]);

            if ((tag = taggify(content, &index)) == NULL) {
              free(new);
              return 0;
            }

            tag_len = strlen(tag);
            content_len = strlen(content);

            new = (char*) realloc(new, sizeof(char) * len + tag_len);

            strcat(new, tag);

            len += tag_len;
            cursor += tag_len;
          }
        }

        free(content);
        free(tag);
      }

    } else
      new[cursor++] = format[i];
  }

  new[cursor] = '\0';

  if (top > 0)
    return init - 1;

  *target = new;
  return -1;
}

void print(const char *format, ...) {
  char *new = NULL;
  int err;

  if((err = validateFormat(format, &new)) >= 0) {
    free(new);
    fprintf(stderr, "Wrong format at position %d\n", err);
    exit(2);
  }

  va_list args;
  va_start(args, format);
  vprintf(new, args);
  va_end(args);

  free(new);
}
