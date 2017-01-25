#ifndef _LEVENSTEIN_DISTANCE_H_
#define _LEVENSTEIN_DISTANCE_H_

int distance(wchar_t*, int, wchar_t*, int);
int minimum(int, int, int);
void print_distance(wchar_t*, wchar_t*);
void print_distance_in_table(wchar_t*, wchar_t*, int, int);
void print_distance_of_combinations(wchar_t**, int);
void print_distance_of_combinations_part(wchar_t**, int, int);

typedef union WLang
{
    struct
    {
        wchar_t* lang;
        wchar_t* word;
    };
    wchar_t* as_array[2];
} l_word;

l_word* l_w_create(wchar_t* word, wchar_t* lang);

#endif
