#ifndef CFG_H
#define CFG_H

#define CFG_MAX_SECTION_LENGTH 32
#define CFG_MAX_KEY_LENGTH 16
#define CFG_MAX_VALUE_LENGTH 5
#define CFG_DEFAULT_SECTION_NAME L"default"
#define CFG_SECTION_FORMAT L"[%s]"
#define CFG_KEY_NONEXISTING L"absent"

typedef union kvp
{
    struct
    {
        wchar_t* key;
        wchar_t* value;
    };
    wchar_t* as_array[2];
} key_value_pair;

key_value_pair* kvp_create(wchar_t* key, wchar_t* value);
key_value_pair* kvp_from_string(wchar_t* string, const wchar_t* separator);
void kvp_delete(key_value_pair* kvp1);

typedef struct CfgSection
{
    wchar_t* name;
    key_value_pair* pairs;
    unsigned int pairs_count;
} cfg_section;

cfg_section* cfg_s_create(wchar_t* name, key_value_pair* pairs, int pairs_count);
cfg_section* cfg_s_create_empty(wchar_t* name);
void cfg_s_add_opt(cfg_section* section, key_value_pair* pair);
void cfg_s_rm_opt(cfg_section* section, key_value_pair* pair, unsigned int index);
cfg_section* cfg_s_from_line(wchar_t* line);
cfg_section** cfg_s_from_file(const char* filename, unsigned int* result_length);
wchar_t* cfg_s_get_value_by_name(cfg_section* section, wchar_t* name);
void cfg_s_delete(cfg_section* section);

typedef struct CfgFile
{
    wchar_t* path;
    cfg_section** sections;
    unsigned int sections_count;
} cfg_file;

cfg_file* cfg_f_read(wchar_t* filename);
void cfg_f_write(cfg_file* file);

#endif
