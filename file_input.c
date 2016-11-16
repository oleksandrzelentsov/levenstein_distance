#include "file_input.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_lines(char* filename)
{
    FILE* fp = fopen(filename, "rb");
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
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
        return NULL;
    while((read = getline(&line, &length, fp)) != -1)
    {
        result[i] = calloc(length, sizeof(char));
        strcpy(line, result[i]);
        char* temp = calloc(100, sizeof(char));
        sprintf(temp, "%lu", length);
        debug("length:");
        debug(temp);
        debug("read:");
        debug(result[i]);
        ++i;
    }
    fclose(fp);
    return result;
}

