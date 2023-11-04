#include "file_utils.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

char *read_all_bytes(char *file_name, size_t *bytes_read) {
    char *ret = NULL;
    FILE *fp = NULL;

    if(bytes_read) {
        *bytes_read = 0;
    }

    fp = fopen(file_name, "rb");
    if(!fp) {
        goto out;
    }

    fseek(fp, 0L, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    ret = malloc(size);
    if(!ret) {
        goto out;
    }

    size_t tmp_bytes_read = fread(ret, 1, size, fp);
    if(bytes_read) {
        *bytes_read = tmp_bytes_read;
    }

out:
    if(fp) {
        fclose(fp);
    }
    return ret;
}

int write_all_bytes(char *file_name, char *bytes, size_t num_bytes) {
    int ret = -1;
    FILE *fp = NULL;

    fp = fopen(file_name, "wb");
    if(!fp) {
        goto out;
    }

    if(fwrite(bytes, 1, num_bytes, fp) == num_bytes) {
        ret = 0;
    }

out:
    if(fp) {
        fclose(fp);
    }
    return ret;
}
