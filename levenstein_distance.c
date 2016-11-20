#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "levenstein_distance.h"

#ifndef _LEVENSTEIN_DISTANCE_C_
#define _LEVENSTEIN_DISTANCE_C_

int distance(char *s, int len_s, char *t, int len_t)
{
    int cost;

    /* base case: empty strings */
    if (len_s == 0) return len_t;
    if (len_t == 0) return len_s;

    /* test if last characters of the strings match */
    if (s[len_s - 1] == t[len_t - 1])
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

void print_distance(char* a, char* b)
{
    print_distance_in_table(a, b, strlen(a), strlen(b));
}

void print_distance_in_table(char* a, char* b, int a_length, int b_length)
{
    // counting the distance
    int d = distance(a,
                     strlen(a),
                     b,
                     strlen(b));
    char* format_string = calloc(100, sizeof(char));
    sprintf(format_string, "| %%%is | %%%is | %%i\n", a_length, b_length);
    printf(format_string, a, b, d);
}

void print_distance_of_combinations(char** words, int length)
{
    int max_length = 0;
    for(int i = 0; i < length - 1; ++i)
    {
        int t = strlen(words[i]);
        max_length = (max_length < t) ? t : max_length;
    }
    for(int i = 0; i < length - 1; ++i)
    {
        for (int j = i + 1; j < length; ++j)
        {
            print_distance_in_table(words[i], words[j], max_length, max_length);
        }
    }
}

void print_distance_of_combinations_part(char** words, int length, int index)
{
    if (!(index < length && index >= 0))
        return;
    int max_length = 0;
    for(int i = 0; i < length - 1; ++i)
    {
        int t = strlen(words[i]);
        max_length = (max_length < t) ? t : max_length;
    }
    printf("Odległość Levenstein'a od %s do:\n", words[index]);
    for(int i = 0; i < length; ++i)
    {
        if (index == i)
            continue;
        print_distance_in_table(words[index], words[i], strlen(words[index]), max_length);
    }
}

#endif
