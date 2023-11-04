#include "file_utils.h"

#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

const char begin_template[] = "char %s[] = {\n    ";
#define BT_EMPTY_LEN (sizeof("char [] = {\n    ") - 1)

const char byte_format[] = "0x%02X";
#define BF_LEN (sizeof("0x00") - 1)

const char non_16_separator[] = ", ";
#define N16S_LEN (sizeof(non_16_separator) - 1)

const char per_16_separator[] = ",\n    ";
#define P16S_LEN (sizeof(per_16_separator) - 1)

const char ending[] = "\n};\n";
#define ENDING_LEN (sizeof(ending) - 1)

size_t get_output_size(size_t num_bytes, char *var_name) {
    size_t ret = BT_EMPTY_LEN;

    ret += strlen(var_name);
    for(size_t i = 0; i < num_bytes; i++) {
        ret += BF_LEN;
        if(i != num_bytes - 1) {
            if(i % 16 == 15) {
                ret += P16S_LEN;
            } else {
                ret += N16S_LEN;
            }
        }
    }
    ret += ENDING_LEN;
    ret += 1;  /* terminating null byte */

    return ret;
}

#define OUT_APPEND(out_ptr, format...) \
    sprintf_ret = sprintf(out_ptr, format); \
    if(sprintf_ret < 0) { \
        goto out; \
    } \
    out_ptr += sprintf_ret

int write_output_text(char *output, char *bytes, size_t num_bytes, char *var_name) {
    int ret = -1;
    int sprintf_ret = 0;
    char *out_ptr = output;

    OUT_APPEND(out_ptr, begin_template, var_name);
    for(size_t i = 0; i < num_bytes; i++) {
        OUT_APPEND(out_ptr, byte_format, (uint8_t)bytes[i]);
        if(i != num_bytes - 1) {
            if(i % 16 == 15) {
                OUT_APPEND(out_ptr, per_16_separator);
            } else {
                OUT_APPEND(out_ptr, non_16_separator);
            }
        }
    }
    OUT_APPEND(out_ptr, ending);

    ret = 0;
out:
    return ret;
}

int main(int argc, char *argv[]) {
    int ret = -2;
    int write_ret = 0;
    char *file_bytes = NULL;
    size_t num_bytes = 0;
    char *file_text = NULL;
    size_t text_size = 0;

    if(argc != 4) {
        printf("Wrong number of arguments\n"
               "Usage: bin_to_c <input file> <variable name> <output file>\n");
        goto out;
    }

    ret = -1;

    file_bytes = read_all_bytes(argv[1], &num_bytes);
    if(!file_bytes) {
        printf("Failed to read binary file\n");
        goto out;
    }

    text_size = get_output_size(num_bytes, argv[2]);
    file_text = malloc(text_size);
    if(!file_text) {
        printf("Failed to allocate memory for output text\n");
        goto out;
    }

    write_ret = write_output_text(file_text, file_bytes, num_bytes, argv[2]);
    if(write_ret) {
        printf("Failed to generate output text\n");
        goto out;
    }

    /* Don't include the trailing null byte in the file */
    write_ret = write_all_bytes(argv[3], file_text, text_size - 1);
    if(write_ret) {
        printf("Failed to write output file\n");
        goto out;
    }

    ret = 0;
    printf("Success\n");
out:
    if(file_bytes) {
        free(file_bytes);
    }
    if(file_text) {
        free(file_text);
    }
    return ret;
}
