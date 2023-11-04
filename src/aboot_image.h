#ifndef _ABOOT_IMAGE_H
#define _ABOOT_IMAGE_H

#include <stdint.h>
#include <stddef.h>

/* Note: This does not contain all information in an aboot image. */
typedef struct {
    uint32_t img_base;

    uint32_t code_size;
    char *code_ptr;
    uint32_t sig_size;
    char *sig_ptr;
    uint32_t certs_size;
    char *certs_ptr;

    char *_buffer;
    size_t _buf_len;
} aboot_image;

aboot_image *aboot_image_read(char *file_name);

void aboot_image_delete(aboot_image *image);

#endif
