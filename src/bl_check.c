#include "bl_check.h"
#include "config.h"
#include "crc.h"

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char *find_bytes(char *mem, size_t mem_len, char *to_find, size_t to_find_len) {
    char *ret = NULL;

    for(size_t i = 0; i <= mem_len - to_find_len; i++) {
        size_t j = 0;
        while(j < to_find_len && mem[i + j] == to_find[j]) {
            j++;
        }
        if(j == to_find_len) {
            ret = &mem[i];
            break;
        }
    }

    return ret;
}

char *get_next_string(char *mem, size_t mem_len, char *curr_ptr) {
    char *ret = NULL;

    if(!curr_ptr) {
        goto out;
    }

    size_t i = curr_ptr - mem;
    size_t j;

    /* Get to the end of the current string */
    while(i < mem_len && mem[i] != 0) {
        i++;
    }

    /* Get to the start of the next string */
    while(i < mem_len && mem[i] == 0) {
        i++;
    }

    /* Make sure the next string terminates */
    j = i;
    while(j < mem_len && mem[j] != 0) {
        j++;
    }

    if(i != mem_len && j != mem_len) {
        ret = mem + i;
    }

out:
    return ret;
}

bootloader_config *get_config_from_crc(char *bl_code, size_t bl_code_len) {
    bootloader_config *config = NULL;
    uint32_t bl_crc = 0;

    bl_crc = crc32(bl_code, bl_code_len);
    for(size_t i = 0; i < num_configs; i++) {
        if(configs[i].code_crc == bl_crc) {
            config = &configs[i];
            break;
        }
    }

    return config;
}

char bl_equals_str[] = "androidboot.bootloader=%s";

bootloader_config *get_config_from_string(char *bl_code, size_t bl_code_len) {
    bootloader_config *config = NULL;
    char *bl_str = NULL;

    bl_str = find_bytes(bl_code, bl_code_len, bl_equals_str, sizeof(bl_equals_str));
    bl_str = get_next_string(bl_code, bl_code_len, bl_str);

    if(!bl_str) {
        goto out;
    }

    for(size_t i = 0; i < num_configs; i++) {
        if(!strcmp(configs[i].name, bl_str)) {
            config = &configs[i];
            break;
        }
    }

out:
    return config;
}

bootloader_config *get_config(char *bl_code, size_t bl_code_len) {
    bootloader_config *ret = NULL;

    if(bl_code_len < 0x40000) {
        goto out;
    }

    ret = get_config_from_crc(bl_code, bl_code_len);

    if(!ret) {
        ret = get_config_from_string(bl_code, bl_code_len);
        if(ret) {
            printf("WARNING: CRC Mismatch\n");
        }
    }

    if(ret) {
        printf("Bootloader found: %s\n", ret->name);
    } else {
        printf("Unsupported bootloader\n");
    }

out:
    return ret;
}
