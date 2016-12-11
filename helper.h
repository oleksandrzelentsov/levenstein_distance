#include <wchar.h>
#ifndef _HELPER_H_
#define _HELPER_H_

void error(char* message);
void debug(char* message);
void debug_w(wchar_t* message);
void debug_i(int number);
void debug_c(char c);
void debug_wc(wchar_t wc);
int index_of_string_in_strings(char* strings[], int strings_length, char* string);
void print_string_array(wchar_t** res, int a);

#endif
