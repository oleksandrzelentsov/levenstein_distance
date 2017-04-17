#include <levenstein_distance.h>
#include <wchar.h>
#ifndef _STATISTICS_H_
#define _STATISTICS_H_

typedef struct pair_info
{
    union
    {
        wchar_t* words[2];
        struct
        {
            wchar_t* word1;
            wchar_t* word2;
        };
        struct
        {
            wchar_t* w1;
            wchar_t* w2;
        };
    };
    union
    {
        unsigned int distance;
        unsigned int d;
        unsigned int difference;
    };
} PairInfo;

PairInfo get_pair_info(wchar_t*, wchar_t*);

void print_words_with_min_distance(wchar_t** words, int);
void print_words_with_max_distance(wchar_t** words, int);
void print_distance_distribution(wchar_t** words, int);
void print_sorted_by_distance(wchar_t** words, int);

#endif
