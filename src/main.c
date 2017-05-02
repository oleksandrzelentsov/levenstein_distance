#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <sys/stat.h>

#include "helper.h"
#include "levenstein_distance.h"
#include "file_input.h"
#include "cfg.h"
#include "statistics.h"

#ifndef _MAIN_C_
#define _MAIN_C_

static char* bin_filename;
const char* default_input_filename = "./lwords.txt";
const char* default_program_locale = "";
const int debug_on = 0;
int DEBUG = 1;

void usage();
char* get_filename(char*[], int);
int get_index(char*[], int);
char* get_program_locale(char*[], int);
char* get_string_argument(char*[], int, char*, const char*);

int main(int argc, char* argv[])
{
    DEBUG = index_of_string_in_strings(argv, argc, "-v") >= 0 || debug_on;
    // enabling Polish characters
    setlocale(LC_ALL, get_string_argument(argv, argc, "--locale", default_program_locale));

    // setting global bin_filename variable
    bin_filename = argv[0];
    char* arg_filename = get_string_argument(argv, argc, "--filename", default_input_filename);
    int arg_help = index_of_string_in_strings(argv, argc, "-h") +
                   index_of_string_in_strings(argv, argc, "--help") >= 0;

    // setting index of word
    int index = get_index(argv, argc);
    if (index != -1)
    {
        sscanf(argv[index], "%i", &index);
    }
    struct stat buf;
    if (arg_help)
    {
        usage();
        return 0;
    }
    // basic functionality
    if (argc == 3 &&
        index_of_string_in_strings(argv, argc, "--filename") == -1 &&
        index_of_string_in_strings(argv, argc, "--average") == -1 &&
        index_of_string_in_strings(argv, argc, "--locale") == -1 &&
        index_of_string_in_strings(argv, argc, "--index") == -1)
    {
        wchar_t* a1 = calloc(120, sizeof(wchar_t));
        wchar_t* a2 = calloc(120, sizeof(wchar_t));
        mbstowcs(a1, argv[1], 120);
        mbstowcs(a2, argv[2], 120);
        print_distance(a1, a2);
    }
    else if (!stat(arg_filename, &buf))
    {
        int a = 0;
        debug("reading from file");
        debug(arg_filename);
        wchar_t** res = get_lines_from_file(arg_filename, &a);
        debug("returned from function, count:");
        debug_i(a);
        if (index != -1)
        {
            if(index_of_string_in_strings(argv, argc, "--average") >= 0)
            {
                print_average_difference_one(res, a, index);
            }
            else
            {
                debug("printing distance of combinations using index");
                print_distance_of_combinations_part(res, a, index);
            }
        }
        else
        {
            if(index_of_string_in_strings(argv, argc, "--average") >= 0)
            {
                print_average_difference(res, a);
            }
            else
            {
                debug("printing distance of combinations");
                print_distance_of_combinations(res, a);
            }
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
    printf("użycie:\n");
    printf("%s <-h|--help>\n", bin_filename);
    printf("%s <słowo1> <słowo2>\n", bin_filename);
    printf("%s [--filename FILENAME] [--index N]\n", bin_filename);
    printf("\n");
    printf("-h\n"
           "--help\n"
           "ten komunikat\n");
    printf("\n");
    printf("<słowo1>\n"
           "<słowo2>\n"
           "porównanie dwóch słów\n\n");
    printf("--filename FILENAME\n"
           "porównanie wszystkich słów z pliku FILENAME (domyślnie %s)\n\n", default_input_filename);
    printf("--index N\n    domyślnie w porównaniu występują wszystkie kombinacje słów\n");
    printf("    jeśli napisać argument N to w porównaniu pojawią się tylko\n");
    printf("    kombinacje ze słowem w pliku FILENAME\n\n");
    printf("--average\n"
           "    średnia wartość różnic\n\n");
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
                           (char*)argv[filename_idx] :
                           (char*)default_value;
    return input_filename;
}

#endif
