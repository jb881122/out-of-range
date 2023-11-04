#include "aboot_image.h"
#include "file_utils.h"
#include "little_endian.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

aboot_image *aboot_image_read(char *file_name) {
    aboot_image *ret = NULL;
    aboot_image *image = NULL;
    char *file_bytes = NULL;
    size_t num_bytes = 0;
    uint32_t img_base = 0;
    uint32_t offset_val = 0;
    uint32_t code_offset = 0;
    uint32_t code_size = 0;
    uint32_t code_end = 0;
    uint32_t sig_offset = 0;
    uint32_t sig_size = 0;
    uint32_t sig_end = 0;
    uint32_t certs_offset = 0;
    uint32_t certs_size = 0;
    uint32_t img_size = 0;

    file_bytes = read_all_bytes(file_name, &num_bytes);
    if(!file_bytes) {
        goto out;
    }

    /* Make sure we can parse this file as an aboot image */

    offset_val = 0x28;
    if(num_bytes < offset_val
            || le_uint32_read(file_bytes, 0x0) != 0x5
            || le_uint32_read(file_bytes, 0x4) != 0x3) {
        goto out;
    }

    img_base = le_uint32_read(file_bytes, 0xC);
    code_offset = offset_val;
    code_size = le_uint32_read(file_bytes, 0x14);
    code_end = img_base + code_size;

    offset_val += code_size;
    sig_offset = offset_val;
    sig_size = le_uint32_read(file_bytes, 0x1C);
    sig_end = code_end + sig_size;

    offset_val += sig_size;
    certs_offset = offset_val;
    certs_size = le_uint32_read(file_bytes, 0x24);

    offset_val += certs_size;
    img_size = code_size + sig_size + certs_size;
    if(num_bytes < offset_val
            || le_uint32_read(file_bytes, 0x18) != code_end
            || le_uint32_read(file_bytes, 0x20) != sig_end
            || le_uint32_read(file_bytes, 0x10) != img_size) {
        goto out;
    }

    image = malloc(sizeof(aboot_image));
    if(!image) {
        goto out;
    }

    /* Now fill out the aboot_image structure */
    image->_buffer = file_bytes;
    image->_buf_len = num_bytes;
    image->img_base = img_base;
    image->code_ptr = file_bytes + code_offset;
    image->code_size = code_size;
    image->sig_ptr = file_bytes + sig_offset;
    image->sig_size = sig_size;
    image->certs_ptr = file_bytes + certs_offset;
    image->certs_size = certs_size;

    ret = image;
out:
    if(!ret) {
        if(image) {
            free(image);
        }
        if(file_bytes) {
            free(file_bytes);
        }
    }
    return ret;
}

void aboot_image_delete(aboot_image *image) {
    free(image->_buffer);
    free(image);
}
