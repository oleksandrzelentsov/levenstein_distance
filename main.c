#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/stat.h>

#include "levenstein_distance.h"

#ifndef between
#define between(A,X,Y) ((A) < (Y) && (A) >= (X))
#endif

static char* bin_filename;

void error(char* message);
void debug(char* message);
void usage();
void print_distance(char* a, char* b);
int index_of_string_in_strings(char* strings[], int strings_length, char* string);

int main(int argc, char* argv[])
{
    // enabling Polish characters
    setlocale(LC_ALL, "");
    // setting global bin_filename variable
    bin_filename = argv[0];
    int filename_idx = index_of_string_in_strings(argv, argc, "--filename") + 1;
    char* input_filename = (between(filename_idx, 0, argc)) ?
                           argv[filename_idx] :
                           "./lwords.txt";
    /* if we don't have enough arguments,
     * check the file, or
     * end program with an error message
     * as well as the typical usage message */
    if (argc < 3)
    {
        struct stat buf;
        if (stat(input_filename, &buf))
        {
            // todo implement new behavior
            printf("here will be the behavior with file input\n");
            return 0;
        }
        else
        {
            error("brak argumentów");
            usage();
            return 1;
        }
    }
    else
    {
        // copying words to variables
        char* a = argv[1];
        char* b = argv[2];
        print_distance(a, b);
    }
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
