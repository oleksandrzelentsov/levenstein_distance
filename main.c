#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <sys/stat.h>

#include "helper.h"
#include "levenstein_distance.h"

#ifndef between
#define between(A,X,Y) ((A) < (Y) && (A) >= (X))
#endif

static char* bin_filename;

void usage();

char* get_filename(char*[], int);

int main(int argc, char* argv[])
{
    // enabling Polish characters
    setlocale(LC_ALL, "");
    // setting global bin_filename variable
    bin_filename = argv[0];
    struct stat buf;
    if (!stat(get_filename(argv, argc), &buf))
    {
        // todo implement new behavior
        printf("here will be the behavior with file input\n");
        return 0;
    }
    /* if we don't have enough arguments,
     * check the file, or
     * end program with an error message
     * as well as the typical usage message */
    else if (argc < 3)
    {
        error("brak argumentów");
        usage();
        return 1;
    }
    else // basic functionality
    {
        print_distance(argv[1], argv[2]);
    }
}

void usage()
{
    printf("użycie: %s <słowo1> <słowo2>\n", bin_filename);
}

char* get_filename(char* argv[], int argc)
{
    int filename_idx = index_of_string_in_strings(argv, argc, "--filename");
    filename_idx += (filename_idx == -1) ? 0 : 1;
    debug("Filename_idx:");
    char* temp = calloc(20, sizeof(char));
    sprintf(temp, "%i", filename_idx);
    debug(temp);
    char* input_filename = (between(filename_idx, 0, argc)) ?
                           argv[filename_idx] :
                           "./lwords.txt";
    return input_filename;
}
