#include <stdio.h>
#include <string.h>
#include "levenstein_distance.h"
#include <stdio.h>
#include <string.h>

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
    // counting the distance
    int   d = distance(a,
                       strlen(a),
                       b,
                       strlen(b));
    printf("LD(%s,\n   %s) = %i\n", a, b, d);
}

#endif
