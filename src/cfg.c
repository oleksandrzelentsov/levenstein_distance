#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "cfg.h"

#ifndef CFG_C
#define CFG_C

// kvp functions

key_value_pair* kvp_create(wchar_t* key, wchar_t* value)
{
    key_value_pair* result = (key_value_pair*) malloc(sizeof(key_value_pair));
    result->key = key;
    result->value = value;
    return result;
}

key_value_pair* kvp_from_string(wchar_t* string, const wchar_t* separator)
{
    key_value_pair* result;

    wchar_t* key = (wchar_t*) calloc(CFG_MAX_KEY_LENGTH, sizeof(wchar_t));
    wchar_t* value = (wchar_t*) calloc(CFG_MAX_VALUE_LENGTH, sizeof(wchar_t));

    unsigned int max_format_length = 4 + wcslen(separator);
    wchar_t* format_str = L"%%s%s%%s";
    wchar_t* format_substituted = (wchar_t*) calloc(max_format_length, sizeof(wchar_t));

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

// // Section functions
// 
// cfg_section* cfg_s_create(wchar_t* name, key_value_pair** contents)
// {
//     
// }
// 
// cfg_section* cfg_s_from_file(const wchar_t* filename)
// {
// 
// }
// 
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
