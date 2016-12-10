#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <sys/stat.h>

#include "helper.h"
#include "levenstein_distance.h"
#include "file_input.h"

#ifndef _MAIN_C_
#define _MAIN_C_

#define between(A,X,Y) ((A) < (Y) && (A) >= (X))

static char* bin_filename;
const char* default_input_filename = "./lwords.txt";
const char* default_program_locale = "";

void usage();
char* get_filename(char*[], int);
int get_index(char*[], int);
char* get_program_locale(char*[], int);
char* get_string_argument(char*[], int, char*, const char*);

int main(int argc, char* argv[])
{
    // enabling Polish characters
    setlocale(LC_ALL, get_string_argument(argv, argc, "--locale", default_program_locale));

    // setting global bin_filename variable
    bin_filename = argv[0];
    char* arg_filename = get_string_argument(argv, argc, "--filename", default_input_filename);
    int index = get_index(argv, argc);
    struct stat buf;
    // basic functionality
    if (argc == 3 &&
        index_of_string_in_strings(argv, argc, "--filename") == -1 &&
        index_of_string_in_strings(argv, argc, "--index") == -1)
    {
        print_distance(argv[1], argv[2]);
    }
    else if (!stat(arg_filename, &buf))
    {
        // todo implement new behavior
        int a = 0;
        debug("reading from file");
        debug(arg_filename);
        char** res = get_lines_from_file(arg_filename, &a);
        if (index != -1)
        {
            print_distance_of_combinations_part(res, a, index);
        }
        else
        {
            print_distance_of_combinations(res, a);
        }
    }
    /* if we don't have enough arguments,
     * check the file, or
     * end program with an error message
     * as well as the typical usage message */
    else
    {
        error("brak argumentów albo plik lwords.txt nie istnieje");
        usage();
        return 1;
    }
    return 0;
}

void usage()
{
    printf("użycie: %s <słowo1> <słowo2>\n", bin_filename);
}

int get_index(char* argv[], int argc)
{
    int index_idx = index_of_string_in_strings(argv, argc, "--index");
    index_idx += (index_idx == -1) ? 0 : 1;
    return index_idx;
}

char* get_string_argument(char* argv[], int argc, char* ident_name, const char* default_value)
{
    int filename_idx = index_of_string_in_strings(argv, argc, ident_name);
    filename_idx += (filename_idx == -1) ? 0 : 1;
    debug(ident_name);
    debug_i(filename_idx);
    char* input_filename = between(filename_idx, 0, argc) ?
                           argv[filename_idx] :
                           default_value;
    return input_filename;
}

#endif
