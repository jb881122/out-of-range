#include "boot_image.h"
#include "file_utils.h"
#include "little_endian.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

char boot_magic[] = {'A', 'N', 'D', 'R', 'O', 'I', 'D', '!'};
size_t boot_magic_len = sizeof(boot_magic);

uint32_t round_up_page(uint32_t offset) {
    return (((offset - 1) >> 11) + 1) << 11;
}

boot_image *boot_image_new(void) {
    boot_image *ret = NULL;

    ret = malloc(sizeof(boot_image));
    if(!ret) {
        goto out;
    }

    memset(ret, 0, sizeof(boot_image));
    memcpy(ret->magic, boot_magic, boot_magic_len);

out:
    return ret;
}

boot_image *boot_image_read(char *file_name) {
    boot_image *ret = NULL;
    boot_image *image = NULL;
    char *file_bytes = NULL;
    size_t num_bytes = 0;
    uint32_t offset_val = 0;
    uint32_t kernel_offset = 0;
    uint32_t ramdisk_offset = 0;
    uint32_t second_offset = 0;
    uint32_t dt_offset = 0;
    int truncated_ramdisk = 0;

    file_bytes = read_all_bytes(file_name, &num_bytes);
    if(!file_bytes) {
        goto out;
    }

    /* Make sure we can parse this file as a boot image */
    offset_val = 0x800;
    if(num_bytes < offset_val) {
        goto out;
    }
    if(le_uint32_read(file_bytes, 0x24) != 0x800) {
        goto out;
    }
    kernel_offset = offset_val;
    offset_val += round_up_page(le_uint32_read(file_bytes, 0x8));
    if(num_bytes < offset_val) {
        goto out;
    }
    ramdisk_offset = offset_val;
    offset_val += round_up_page(le_uint32_read(file_bytes, 0x10));
    if(num_bytes < offset_val) {
        truncated_ramdisk = 1;
    } else {
        second_offset = offset_val;
        offset_val += round_up_page(le_uint32_read(file_bytes, 0x18));
        dt_offset = offset_val;
        offset_val += round_up_page(le_uint32_read(file_bytes, 0x28));
        if(num_bytes < offset_val) {
            goto out;
        }
    }

    image = malloc(sizeof(boot_image));
    if(!image) {
        goto out;
    }

    /* Now fill out the boot_image structure */
    image->_buffer = file_bytes;
    image->_buf_len = num_bytes;
    image->_kernel_ptr_separate = 0;
    image->_ramdisk_ptr_separate = 0;
    memcpy(image->magic, file_bytes, boot_magic_len);
    image->kernel_ptr = file_bytes + kernel_offset;
    image->kernel_size = le_uint32_read(file_bytes, 0x8);
    image->kernel_addr = le_uint32_read(file_bytes, 0xC);
    image->ramdisk_ptr = file_bytes + ramdisk_offset;
    image->ramdisk_size_display = le_uint32_read(file_bytes, 0x10);
    image->ramdisk_addr = le_uint32_read(file_bytes, 0x14);
    image->second_addr = le_uint32_read(file_bytes, 0x1C);
    image->tags_addr = le_uint32_read(file_bytes, 0x20);
    if(!truncated_ramdisk) {
        image->ramdisk_size = image->ramdisk_size_display;
        image->second_ptr = file_bytes + second_offset;
        image->second_size = le_uint32_read(file_bytes, 0x18);
        image->dt_ptr = file_bytes + dt_offset;
        image->dt_size = le_uint32_read(file_bytes, 0x28);
    } else {
        image->ramdisk_size = num_bytes - ramdisk_offset;
        image->second_ptr = NULL;
        image->second_size = 0;
        image->dt_ptr = NULL;
        image->dt_size = 0;
    }

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

int boot_image_set_kernel(char *kernel, size_t num_bytes, boot_image *image) {
    int ret = -1;
    char *kernel_copy = NULL;

    kernel_copy = malloc(num_bytes);
    if(!kernel_copy) {
        goto out;
    }

    memcpy(kernel_copy, kernel, num_bytes);
    image->kernel_ptr = kernel_copy;
    image->kernel_size = num_bytes;
    image->_kernel_ptr_separate = 1;

    ret = 0;
out:
    return ret;
}

int boot_image_set_ramdisk(char *ramdisk, size_t num_bytes, boot_image *image) {
    int ret = -1;
    char *ramdisk_copy = NULL;

    ramdisk_copy = malloc(num_bytes);
    if(!ramdisk_copy) {
        goto out;
    }

    memcpy(ramdisk_copy, ramdisk, num_bytes);
    image->ramdisk_ptr = ramdisk_copy;
    image->ramdisk_size = num_bytes;
    image->ramdisk_size_display = num_bytes;
    image->_ramdisk_ptr_separate = 1;

    ret = 0;
out:
    return ret;
}

char *boot_image_to_bytes(boot_image *image, size_t *output_len) {
    char *ret = NULL;
    size_t num_bytes = 0;
    size_t kernel_offset = 0;
    size_t ramdisk_offset = 0;
    size_t second_offset = 0;
    size_t dt_offset = 0;

    if(output_len) {
        *output_len = 0;
    }

    num_bytes = 0x800;
    kernel_offset = num_bytes;
    num_bytes += round_up_page(image->kernel_size);
    ramdisk_offset = num_bytes;
    num_bytes += round_up_page(image->ramdisk_size);
    second_offset = num_bytes;
    num_bytes += round_up_page(image->second_size);
    dt_offset = num_bytes;
    num_bytes += round_up_page(image->dt_size);

    ret = malloc(num_bytes);
    if(!ret) {
        goto out;
    }

    memset(ret, 0, num_bytes);
    if(image->_buffer) {
        memcpy(ret, image->_buffer, 0x800);
    }
    memcpy(ret, image->magic, boot_magic_len);
    le_uint32_write(image->kernel_size, ret, 0x8);
    le_uint32_write(image->kernel_addr, ret, 0xC);
    le_uint32_write(image->ramdisk_size_display, ret, 0x10);
    le_uint32_write(image->ramdisk_addr, ret, 0x14);
    le_uint32_write(image->second_size, ret, 0x18);
    le_uint32_write(image->second_addr, ret, 0x1C);
    le_uint32_write(image->tags_addr, ret, 0x20);
    le_uint32_write(0x800, ret, 0x24);
    le_uint32_write(image->dt_size, ret, 0x28);

    if(image->kernel_size) {
        memcpy(ret + kernel_offset, image->kernel_ptr, image->kernel_size);
    }
    if(image->ramdisk_size) {
        memcpy(ret + ramdisk_offset, image->ramdisk_ptr, image->ramdisk_size);
    }
    if(image->second_size) {
        memcpy(ret + second_offset, image->second_ptr, image->second_size);
    }
    if(image->dt_size) {
        memcpy(ret + dt_offset, image->dt_ptr, image->dt_size);
    }

    if(output_len) {
        *output_len = num_bytes;
    }

out:
    return ret;
}

int boot_image_write(char *file_name, boot_image *image) {
    int ret = -1;
    int write_ret = 0;
    size_t num_bytes = 0;
    char *image_bytes = NULL;

    image_bytes = boot_image_to_bytes(image, &num_bytes);
    if(!image_bytes) {
        goto out;
    }

    write_ret = write_all_bytes(file_name, image_bytes, num_bytes);
    if(write_ret) {
        goto out;
    }

    ret = 0;
out:
    if(image_bytes) {
        free(image_bytes);
    }
    return ret;
}

void boot_image_delete(boot_image *image) {
    free(image->_buffer);
    if(image->_kernel_ptr_separate) {
        free(image->kernel_ptr);
    }
    if(image->_ramdisk_ptr_separate) {
        free(image->ramdisk_ptr);
    }
    free(image);
}
