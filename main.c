#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

static char* filename;

int minimum(int a, int b, int c)
{
    if (a < b)
        if (a < c) return a;
        else return c;
    else if (b < c) return b;
    else return c;
}

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

void error(char* message)
{
    printf("Błąd: %s.\n", message);
}

void usage()
{
    printf("użycie: %s <słowo1> <słowo2>\n", filename);
}

int main(int argc, char* argv[])
{
    // enabling Polish characters
    setlocale(LC_ALL, "");
    // setting global filename variable
    filename = argv[0];
    /* if we don't have enough arguments,
     * end program with an error message
     * as well as the typical usage message
     */
    if (argc < 3)
    {
        error("brak argumentów");
        usage();
        return 1;
    }
    // copying words to variables
    char* a = argv[1];
    char* b = argv[2];
    int   d = distance(a,
                       strlen(a),
                       b,
                       strlen(b));
    printf("LD(%s,\n   %s) = %i\n", a, b, d);
}

