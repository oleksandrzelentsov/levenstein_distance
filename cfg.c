#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "cfg.h"
#include "helper.h"
#include "file_input.h"

#ifndef CFG_C
#define CFG_C

// kvp functions

key_value_pair* kvp_create(wchar_t* key, wchar_t* value)
{
    key_value_pair* result;
    memalloc(result, key_value_pair);
    result->key = key;
    result->value = value;
    return result;
}

key_value_pair* kvp_from_string(wchar_t* string, const wchar_t* separator)
{
    key_value_pair* result;

    wchar_t* key;
    wchar_t* value;

    unsigned int max_format_length = 4 + wcslen(separator);
    wchar_t* format_str = L"%%s%s%%s";
    wchar_t* format_substituted;

    cmemalloc(key, wchar_t, CFG_MAX_KEY_LENGTH);
    cmemalloc(value, wchar_t, CFG_MAX_VALUE_LENGTH);
    cmemalloc(format_substituted, wchar_t, max_format_length);

    swprintf(format_substituted, max_format_length, format_str, separator);
    swscanf(string, format_substituted, key, value);
    result = kvp_create(key, value);
    return result;
}

void kvp_delete(key_value_pair* kvp1)
{
    free(kvp1->key);
    free(kvp1->value);
    free(kvp1);
}

// Section functions

cfg_section* cfg_s_create(wchar_t* name, key_value_pair* pairs, int pairs_count)
{
    cfg_section* result;
    memalloc(result, cfg_section);
    result->name = name;
    result->pairs = pairs;
    result->pairs_count = pairs_count;
    return result;
}

char wtf_is_the_line(wchar_t* line)
/*
 * s - section declaration
 * c - comment
 * b - blank line
 * o - option
 */
{
    unsigned int length = wcslen(line);
    if(line[0] == L'[' && line[length - 1] == L']')
        return 's';
    if(line[0] == L'#' || line[0] == L';')
        return 'c';
    if(length < 5)
        return 'b';
    return 'o';
}

cfg_section** cfg_s_from_file(const char* filename, unsigned int* result_length)
{
    cfg_section** result;
    wchar_t** lines;
    int lines_count;

    cmemalloc(result, cfg_section*, 1);
    lines = get_lines_from_file(filename, &lines_count);
    for(int i = 0; i < lines_count; ++i)
    {
        char line_type = wtf_is_the_line(lines[i]);
        switch(line_type)
        {
        case L's':
            // end current section
            // start new section
            break;
        case L'o':
            // write new kvp
            break;
        case L'b':
            break;
        case L'c':
            break;
        }
    }
    //end current section
    return result;
}

// wchar_t* cfg_s_get_value_by_name(cfg_section section, wchar_t* name)
// {
// 
// }
// 
// void cfg_s_delete(cfg_section section)
// {
// 
// }
// 
// // File functions
// 
// cfg_file cfg_f_read(wchar_t* filename)
// {
// 
// }
// 
// void cfg_f_write(cfg_file file)
// {
// 
// }

#endif
