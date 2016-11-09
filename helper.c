#include "helper.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define DEBUG 1

int index_of_string_in_strings(char* strings[], int strings_length, char* string)
{
    for (int i = 0; i < strings_length; ++i)
    {
        if (!strcmp(string, strings[i]))
            return i;
    }
    return -1;
}

void error(char* message)
{
    printf("Błąd: %s.\n", message);
}

void debug(char* message)
{
    if(DEBUG)
        printf("Debug: %s", message);
}

char* format(char* fmt, ...)
{
    // TODO implementation
}
