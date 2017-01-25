#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "file_input.h"
#include "helper.h"

#ifndef _FILE_INPUT_C_
#define _FILE_INPUT_C_
const int max_line_length = 120;

wchar_t** get_lines_from_file(const char* filename, int* lines_count)
{
    debug("allocating memory");
    FILE* fp = fopen(filename, "rb");
    fwide(fp, 1);

    int skip = 0;

    int line_length = 0;
    wchar_t* line = calloc(max_line_length, sizeof(wchar_t));

    int r_mem_size = 1;
    wchar_t** result = calloc(1, sizeof(wchar_t*));

    int lines = 0;
    debug("beginning loop");
    for(wchar_t ch = fgetwc(fp); !(ch == EOF || ch == WEOF); ch = fgetwc(fp))
    {
        if(ch == '\n' || ch == L'\n')
        {
            if (skip)
            {
                skip = 0;
                continue;
            }
            debug("read EOL");
            debug("-------------------------------------------");
            if (r_mem_size < lines + 1)
            {
                debug("reallocating memory for results");
                wchar_t** t_res = calloc(++r_mem_size, sizeof(wchar_t*));
                for (int i = 0; i < r_mem_size - 1; i++)
                {
                    /* if (result[i] == NULL) */
                    /*     continue; */
                    debug("rewriting");
                    debug_w(result[i]);
                    t_res[i] = calloc(wcslen(result[i]) + 1, sizeof(wchar_t));
                    debug("copying");
                    wcscpy(t_res[i], result[i]);
                }
                //free(result);
                result = t_res;
                debug("array after resize");
                //print_string_array(result, r_mem_size);
            }
            debug("read line:");
            debug_w(line);
            debug("allocating new string size");
            result[lines] = calloc(wcslen(line) + 1, sizeof(wchar_t));
            debug("copying read line to result array");
            wcscpy(result[lines], line);
            debug("array element after copying");
            debug_w(result[lines]);
            free(line);
            debug("allocating new line");
            line = calloc(max_line_length, sizeof(wchar_t));
            debug("new line allocated");
            line_length = 0;
            lines++;
            debug("array state:");
            //print_string_array(result, r_mem_size);
            debug("end array state");
            debug("-------------------------------------------");
        }
        else if (line_length == 0 && (ch == '#' || ch == L'#'))
        {
            skip = 1;
            continue;
        }
        else
        {
            /* char* t = calloc(1, sizeof(char)); */
            /* sprintf(t, "from count lines: %c", ch); */
            /* debug(t); */
            /* free(t); */
            if(skip)
                continue;
            debug("read character");
            debug_wc(ch);
            debug("line now:");
            line[line_length++] = ch;
            line[line_length] = L'\0';
            debug_w(line);
            debug("---------------------");
        }
        debug("reading next character");
    }
    debug("closing fp");
    fclose(fp);
    debug("freeing line");
    free(line);
    *lines_count = lines;
    return result;
}

#endif
