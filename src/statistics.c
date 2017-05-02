#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "statistics.h"
#include "helper.h"

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
    PairInfo* pairs = (PairInfo*)calloc(get_possible_pair_count(len), sizeof(PairInfo));
    int k = 0;
    for(int i = 0; i < len; ++i)
    {
        for(int j = i + 1; j < len; ++j)
        {
            debug("__________");
            debug("create pair:");
            debug_w(words[i]);
            debug_w(words[j]);
            pairs[k++] = get_pair_info(words[i], words[j]);
        }
    }
    assert(k == get_possible_pair_count(len));
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
            /* free(new_pairs); // TODO dangerous place */
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
            if(cmpfunc(pairs[i], pairs[i + 1]) > 0)
            {
                PairInfo c = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = c;
            }
        }
    }
}

void print_pairs(PairInfo* pairs, int len, int flen, int slen)
{
    char* format_string = calloc(100, sizeof(char));
    sprintf(format_string, "| %%%ils | %%%ils | %%i\n", flen, slen);
    for(int i = 0; i < len; ++i)
        printf(format_string, pairs[i].w1, pairs[i].w2, pairs[i].d);
}

void print_words_with_min_distance(wchar_t** words, int len)
{
    int pair_distance_cmp(PairInfo a, PairInfo b)
    {
        return a.d - b.d;
    }

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
    print_pairs(min_dist_pairs, len, col_lengths[0], col_lengths[1]);
}

void print_words_with_max_distance(wchar_t** words, int len)
{
    int pair_distance_cmp(PairInfo a, PairInfo b)
    {
        return a.d - b.d;
    }

    /* longest distance word pairs */
    PairInfo* pairs = get_possible_pairs(words, len);
    sort_pairs(pairs, len, pair_distance_cmp);
    int is_correct_length(PairInfo a)
    {
        return a.d == pairs[len - 1].d;
    }
    int new_len = len;
    PairInfo* max_dist_pairs = filter(pairs, &new_len, is_correct_length);
    /* define column length for both columns */
    int* col_lengths = get_column_length(max_dist_pairs, new_len);
    /* print in table */
    print_pairs(max_dist_pairs, new_len, col_lengths[0], col_lengths[1]);
}

void _print_avg_diff_pairs(PairInfo* pairs, int len)
{
    /* debug("!!!"); */
    /* debug("_p_a_d_p: 1st pair:"); */
    /* debug_w(pairs[0].w1); */
    /* debug_w(pairs[0].w2); */
    /* debug("!!!"); */
    float avg = 0;
    float pair_count = len;
    for(int i = 0; i < pair_count; ++i)
    {
        debug("-------------------");
        debug("pair:");
        debug_w(pairs[i].w1);
        debug_w(pairs[i].w2);
        debug("current pair distance:");
        debug_i(pairs[i].d);
        float avg_component = pairs[i].d / pair_count;
        debug("and it divided by pair count:");
        debug_f(avg_component);
        avg += avg_component;
    }
    debug("-------------------");
    printf("Średnia wartość różnic: %.2f\n", avg);
}

void print_average_difference(wchar_t** words, int len)
{
    PairInfo* pairs = get_possible_pairs(words, len);
    /* debug("!!!"); */
    /* debug("p_a_d: 1st pair:"); */
    /* debug_w(pairs[0].w1); */
    /* debug_w(pairs[0].w2); */
    /* debug("!!!"); */
    int pair_count = get_possible_pair_count(len);
    _print_avg_diff_pairs(pairs, pair_count);
}

void print_average_difference_one(wchar_t** words, int len, int index)
{
    int pair_count = len - 1;
    PairInfo* pairs = (PairInfo*)calloc(pair_count, sizeof(PairInfo));
    for(int i = 0; i < len; ++i)
    {
        if(i < index)
        {
            pairs[i] = get_pair_info(words[index], words[i]);
        }
        else if (i > index)
        {
            pairs[i - 1] = get_pair_info(words[index], words[i]);
        }
    }
    _print_avg_diff_pairs(pairs, pair_count);
}

#endif
