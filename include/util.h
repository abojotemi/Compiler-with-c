#ifndef UTIL_DEF
#define UTIL_DEF
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
char *get_file(const char *file_name, int *size);

int KW_SIZE = 10;
const char *KEYWORDS[] = {"if", "elif", "or", "and", "fn", "int", "return", "anon", "float", "for", "not", "print", "str"};

typedef enum {
    STATUS_OK,
    STATUS_ALLOC_FAILURE,
    STATUS_INVALID_TOKEN,
} Status;
void report_error(const char *msg);
Status safe_realloc(char **ptr, int new_size);


#endif 

