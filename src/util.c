#include "../include/util.h"
#include <stdio.h>
#include <stdlib.h>


void report_error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

Status safe_realloc(char **ptr, int new_size) {
    char *tmp = (char *)realloc(*ptr, new_size);
    if (!tmp) {
        report_error("Memory reallocation failed");
        return STATUS_ALLOC_FAILURE;
    }
    *ptr = tmp;
    return STATUS_OK;
}



char *get_file(const char *file_name, int *size)
{

    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s \n", file_name);
        exit(1);
    }
    if (fseek(file, 0, SEEK_END) == -1)
    {
        fprintf(stderr, "Error seeking in file %s", file_name);
        exit(1);
    }
    int file_size = ftell(file);

    rewind(file);

    char *buf = (char *)malloc(file_size + 1);

    if (buf == NULL)
    {
        fprintf(stderr, "Error allocating memory for file %s \n", file_name);
        exit(1);
    }
    if (fread((void *)buf, file_size, 1, file) <= 0)
    {
        fprintf(stderr, "Error reading from file %s \n", file_name);
        free(buf);
        exit(1);
    }
    buf[file_size] = '\0';
    *size = file_size;
    fclose(file);
    return buf;
}
