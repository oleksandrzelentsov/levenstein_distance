#include "file_input.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#ifndef _FILE_INPUT_C_
#define _FILE_INPUT_C_

int count_lines(char* filename)
{
    FILE* fp = fopen(filename, "r");
    fwide(fp, 1);
    int lines = 0;
    while(!feof(fp))
    {
        char ch = fgetwc(fp);
        if(ch == '\n')
        {
            lines++;
        }
        else if (ch == EOF)
            break;
        else
        {
            char* t = calloc(1, sizeof(char));
            sprintf(t, "from count lines: %c", ch);
            debug(t);
            free(t);
        }
    }
    fclose(fp);
    return lines;
}

char** get_lines_from_file(char* filename, int* lines_count)
{
    debug("counting lines");
    *lines_count = count_lines(filename);
    char** result = calloc(*lines_count, sizeof(char*));
    size_t i = 0;
    char* line = calloc(100, sizeof(char));
    size_t length = 0;
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        return NULL;
    }
    fwide(fp, 1);
    debug("beginning loop");
    while(!feof(fp) && fwscanf(fp, L"%s", (wchar_t*)line) >= 1)
    {
        debug("___________________________________");
        length = wcslen((wchar_t*)line);
        debug("read successful");
        result[i] = calloc(length, sizeof(char));
        debug("memory allocation successful");
        wcscpy((wchar_t*)result[i], (wchar_t*)line);
        debug("copying successful");
        char* temp = calloc(100, sizeof(char));
        sprintf(temp, "%lu", length);
        debug("length:");
        debug(temp);
        debug("read:");
        debug(line);
        ++i;
    }
    fclose(fp);
    return result;
}

#endif
