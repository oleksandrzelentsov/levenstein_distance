#include "file_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_lines(char* filename)
{
    FILE* fp = fopen(filename, "r");
    int lines = 0;
    while(!feof(fp))
    {
        char ch = fgetc(fp);
        if(ch == '\n')
        {
            lines++;
        }
    }
    fclose(fp);
    return lines;
}

char** get_lines_from_file(char* filename, int* lines_count)
{
    *lines_count = count_lines(filename);
    char** result = calloc(*lines_count, sizeof(char*));
    size_t i = 0;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
        return NULL;
    while((read = getline(&line, &length, fp)) != -1)
    {
        result[i] = calloc(length, sizeof(char));
        strcpy(line, result[i]);
        ++i;
    }
    return result;
}

