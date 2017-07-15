#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "helper.h"

#ifndef _HELPER_C_
#define _HELPER_C_
extern int DEBUG;

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
    {
        printf("DEBUG %s\n", message);
    }
}

void debug_i(int number)
{
    if(DEBUG)
    {
        char* temp = calloc(100, sizeof(char));
        sprintf(temp, "%d", number);
        printf("DEBUG %s\n", temp);
        free(temp);
    }
}

void debug_c(char c)
{
    if(DEBUG)
    {
        printf("DEBUG %c\n", c);
    }
}

void debug_wc(wchar_t wc)
{
    if(DEBUG)
    {
        printf("DEBUG %lc\n", wc);
    }
}

void debug_w(wchar_t* message)
{
    if(DEBUG)
    {
        printf("DEBUG %ls\n", message);
    }
}

void print_string_array(wchar_t** res, int a)
{
    for(int i = 0; i < a; ++i)
    {
        printf("%ls\n", res[i]);
    }
}

int between(const int a, const int x, const int y)
{
    return a < y && a >= x;
}

void debug_f(float message)
{
    if(DEBUG)
    {
        printf("DEBUG %.2f\n", message);
    }
}

int file_exists(const char* filename)
{
    return access( filename, F_OK ) != -1;
}

#endif
