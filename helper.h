#include <wchar.h>
#ifndef _HELPER_H_
#define _HELPER_H_

#define DEBUG 0
#define memalloc(A,B) A=(B*)malloc(sizeof(B))
#define cmemalloc(A,B,C) A=(B*)calloc(C,sizeof(B))

void error(char* message);
void debug(char* message);
void debug_w(wchar_t* message);
void debug_i(int number);
void debug_c(char c);
void debug_wc(wchar_t wc);
int index_of_string_in_strings(char* strings[], int strings_length, char* string);
void print_string_array(wchar_t** res, int a);
int between(const int a, const int x, const int y);
int file_exists(const char* filename);

#endif
