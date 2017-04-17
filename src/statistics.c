#include <stdlib.h>
#include "statistics.h"

#ifndef _STATISTICS_C_
#define _STATISTICS_C_

PairInfo get_pair_info(wchar_t* w1, wchar_t* w2)
{
    PairInfo* p = malloc(sizeof(PairInfo));
    p->word1 = w1;
    p->word2 = w2;
    p->distance = distance(w1, wcslen(w1), w2, wcslen(w2));
    return *p;
}

int get_possible_pair_count(int n)
{
    return n * (n - 1) / 2;
}

int max_length(wchar_t** words, int len)
{
    int res = 0;
    for(int i = 0; i < len; ++i)
    {
        int a = wcslen(words[i]);
        if (a > res)
            res = a;
    }
    return res;
}

PairInfo* get_possible_pairs(wchar_t** words, int len)
{
    PairInfo* pairs = calloc(get_possible_pair_count(len), sizeof(PairInfo));
    for(int i = 0; i < len; ++i)
    {
        for(int j = i + 1; j < len; ++j)
        {
            pairs[i] = get_pair_info(words[i], words[j]);
        }
    }
    return pairs;
}

int* get_column_length(PairInfo* pairs, int len)
{
    int* col_lengths = calloc(2, sizeof(int));
    col_lengths[0] = 0;
    col_lengths[1] = 0;
    for(int i = 0; i < len; ++i)
    {
        int a = wcslen(pairs[i].w1);
        int b = wcslen(pairs[i].w2);
        if(col_lengths[0] < a)
            col_lengths[0] = a;
        if(col_lengths[1] < b)
            col_lengths[1] = b;
    }
    return col_lengths;
}

PairInfo* filter(PairInfo* pairs, int* rlen, int (*ffunc)(PairInfo))
{
    PairInfo* new_pairs = NULL;
    int new_length = 0;
    int len = *rlen;
    for(int i = 0; i < len; ++i)
    {
        if(ffunc(pairs[i]))
        {
            PairInfo* temp = calloc(new_length + 1, sizeof(PairInfo));
            for(int j = 0; j < new_length; ++j)
                temp[j] = new_pairs[j];
            temp[new_length++] = pairs[i];
            free(new_pairs); // TODO dangerous place
            new_pairs = temp;
        }
    }
    *rlen = new_length;
    return new_pairs;
}

void sort_pairs(PairInfo* pairs, int len, int (*cmpfunc)(PairInfo, PairInfo))
{
    for(int k = 0; k < len; ++k)
    {
        for(int i = 0; i < len - 1; ++i)
        {
            if(cmpfunc(pairs[i], pairs[i + 1]) < 0)
            {
                PairInfo c = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = c;
            }
        }
    }
}

int pair_distance_cmp(PairInfo a, PairInfo b)
{
    return a.d - b.d;
}

void print_words_with_min_distance(wchar_t** words, int len)
{
    /* shortest distance word pairs */
    PairInfo* pairs = get_possible_pairs(words, len);
    sort_pairs(pairs, len, pair_distance_cmp);
    int is_correct_length(PairInfo a)
    {
        return a.d == pairs[0].d;
    }
    PairInfo* min_dist_pairs = filter(pairs, &len, is_correct_length);
    /* define column length for both columns */
    int* col_lengths = get_column_length(min_dist_pairs, len);
    /* print in table */
}

void print_words_with_max_distance(wchar_t** words, int len)
{
    /* longest distance word pairs */
    /* define column length for both columns */
    /* print in table */
}

void print_distance_distribution(wchar_t** words, int len)
{

}

void print_sorted_by_distance(wchar_t** words, int len)
{

}

#endif
