#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "levenstein_distance.h"

static char* bin_filename;

void error(char* message)
{
    printf("Błąd: %s.\n", message);
}

void usage()
{
    printf("użycie: %s <słowo1> <słowo2>\n", bin_filename);
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

int main(int argc, char* argv[])
{
    // enabling Polish characters
    setlocale(LC_ALL, "");
    // setting global bin_filename variable
    bin_filename = argv[0];
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
    print_distance(a, b);
}

