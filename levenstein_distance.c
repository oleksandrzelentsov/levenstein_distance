#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include "helper.h"
#include "levenstein_distance.h"

#ifndef _LEVENSTEIN_DISTANCE_C_
#define _LEVENSTEIN_DISTANCE_C_

int distance(wchar_t *s, int len_s, wchar_t *t, int len_t)
{
    int cost;
    wchar_t c1 = towlower(s[len_s - 1]);
    wchar_t c2 = towlower(t[len_t - 1]);

    /* base case: empty strings */
    if (len_s == 0) return len_t;
    if (len_t == 0) return len_s;

    /* test if last characters of the strings match */
    if (c1 == c2)
        cost = 0;
    else
        cost = 1;

    /* return minimum of
     * delete char from s,
     * delete char from t,
     * and delete char from both
     */
    return minimum(distance(s, len_s - 1, t, len_t    ) + 1,
                   distance(s, len_s    , t, len_t - 1) + 1,
                   distance(s, len_s - 1, t, len_t - 1) + cost);
}

int minimum(int a, int b, int c)
{
    if (a < b)
        if (a < c) return a;
        else return c;
    else if (b < c) return b;
    else return c;
}

void print_distance(wchar_t* a, wchar_t* b)
{
    print_distance_in_table(a, b, wcslen(a), wcslen(b));
}

void print_distance_in_table(wchar_t* a, wchar_t* b, int a_length, int b_length)
{
    // counting the distance
    int d = distance(a,
                     wcslen(a),
                     b,
                     wcslen(b));
    char* format_string = calloc(100, sizeof(char));
    sprintf(format_string, "| %%%ils | %%%ils | %%i\n", a_length, b_length);
    printf(format_string, a, b, d);
}

void print_distance_of_combinations(wchar_t** words, int length)
{
    int max_length = 0;
    debug("measuring max length of words");
    for(int i = 0; i < length - 1; ++i)
    {
        int t = wcslen(words[i]);
        max_length = (max_length < t) ? t : max_length;
        debug_i(max_length);
    }
    debug("printing distances");
    for(int i = 0; i < length - 1; ++i)
    {
        for (int j = i + 1; j < length; ++j)
        {
            print_distance_in_table(words[i], words[j], max_length, max_length);
        }
    }
}

void print_distance_of_combinations_part(wchar_t** words, int length, int index)
{
    if (!(index < length && index >= 0))
        return;
    int max_length = 0;
    for(int i = 0; i < length - 1; ++i)
    {
        int t = wcslen(words[i]);
        max_length = (max_length < t) ? t : max_length;
    }
    printf("Odległość Levenstein'a od %ls do:\n", words[index]);
    for(int i = 0; i < length; ++i)
    {
        if (index == i)
            continue;
        print_distance_in_table(words[index], words[i], wcslen(words[index]), max_length);
    }
}

#endif
