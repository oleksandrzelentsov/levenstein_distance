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

cfg_section* cfg_s_create_empty(wchar_t* name)
{
    return cfg_s_create(name, NULL, 0);
}

void cfg_s_add_opt(cfg_section* section, key_value_pair* pair)
{
    // create new array of opions with n+1 items
    key_value_pair* n_pairs;
    cmemalloc(n_pairs, key_value_pair, section->pairs_count + 1);
    // rewrite existing ones
    for(int i = 0; i < section->pairs_count; ++i)
    {
        n_pairs[i] = section->pairs[i];
    }
    // add new one
    n_pairs[section->pairs_count++] = *pair;
    key_value_pair* temp = section->pairs;
    section->pairs = n_pairs;
    free(temp);
}

void cfg_s_rm_opt(cfg_section* section, key_value_pair* pair, unsigned int index)
{
    // create new array of opions with n-1 items
    key_value_pair* n_pairs;
    cmemalloc(n_pairs, key_value_pair, section->pairs_count - 1);
    // rewrite existing ones
    for(int i = 0; i < index; ++i)
    {
        n_pairs[i] = section->pairs[i];
    }
    // rewrite all except prev ones
    for(int i = index + 1; i < section->pairs_count; ++i)
    {
        n_pairs[i] = section->pairs[i + 1];
    }
    key_value_pair* temp = section->pairs;
    section->pairs = n_pairs;
    free(temp);
}

cfg_section* cfg_s_from_line(wchar_t* line)
{
    cfg_section* result;
    memalloc(result, cfg_section);
    result->pairs = NULL;
    result->pairs_count = 0;
    cmemalloc(result->name, wchar_t, CFG_MAX_SECTION_LENGTH);
    swscanf(line, CFG_SECTION_FORMAT, result->name);
    return result;
}

char wtf_is_the_line(wchar_t* line)
{
    /*
     * s - section declaration
     * c - comment
     * b - blank line
     * o - option
     */
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
    cfg_section* current_section = cfg_s_create_empty(CFG_DEFAULT_SECTION_NAME);
    key_value_pair* current_kvp;
    wchar_t** lines;
    int lines_count;

    cmemalloc(result, cfg_section*, 1);
    memalloc(current_kvp, key_value_pair);
    lines = get_lines_from_file(filename, &lines_count);
    for(int i = 0; i < lines_count; ++i)
    {
        char line_type = wtf_is_the_line(lines[i]);
        switch(line_type)
        {
        case 's':
            // end current section
            cfg_section** n_result;
            cmemalloc(n_result, cfg_section*, *result_length + 1);
            for(int i = 0; i < *result_length; ++i)
            {
                n_result[i] = result[i];
            }
            result[(*result_length)++] = current_section;
            // start new section
            current_section = cfg_s_from_line(lines[i]);
            break;
        case 'o':
            // write new kvp
            cfg_s_add_opt(current_section, kvp_from_string(lines[i], L'='));
            break;
        case 'b':
            break;
        case 'c':
            break;
        default:
            break;
        }
    }

    //end current section
    cfg_section** n_result;
    cmemalloc(n_result, cfg_section*, *result_length + 1);
    for(int i = 0; i < *result_length; ++i)
    {
        n_result[i] = result[i];
    }
    result[(*result_length)++] = current_section;

    return result;
}

wchar_t* cfg_s_get_value_by_name(cfg_section* section, wchar_t* name)
{
    for(int i = 0; i < section->pairs_count; ++i)
    {
        if(wcscoll(section->pairs[i]->name, name) == 0)
        {
            return section->pairs[i]->value;
        }
    }
    return CFG_KEY_NONEXISTING;
}

void cfg_s_delete(cfg_section* section)
{
    for(int i = 0; i < section->pairs_count; ++i)
    {
        free(section->pairs[i]);
    }
    free(section->pairs);
    free(section->name);
    free(section);
}

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
