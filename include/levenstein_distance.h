#include <wchar.h>
#ifndef _LEVENSTEIN_DISTANCE_H_
#define _LEVENSTEIN_DISTANCE_H_

int distance(wchar_t*, int, wchar_t*, int);
int distance_exclusions(wchar_t*, int, wchar_t*, int, cfg_file*)
int minimum(int, int, int);
void print_distance(wchar_t*, wchar_t*);
void print_distance_in_table(wchar_t*, wchar_t*, int, int);
void print_distance_of_combinations(wchar_t**, int);
void print_distance_of_combinations_part(wchar_t**, int, int);

#endif
