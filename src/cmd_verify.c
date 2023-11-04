#include "cmd_verify.h"
#include "config.h"
#include "boot_image.h"
#include "aboot_image.h"
#include "crc.h"
#include "little_endian.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

int cmd_verify_main(int argc, char *argv[]) {
    int ret = -2;
    aboot_image *bootloader = NULL;
    boot_image *image = NULL;
    char *bl_code = NULL;
    char *image_kernel = NULL;
    size_t num_bytes = 0;
    uint32_t bl_crc = 0;
    uint32_t image_crc = 0;

    if(argc != 4) {
        printf("Wrong number of arguments\n");
        goto out;
    }

    ret = -1;

    bootloader = aboot_image_read(argv[2]);
    if(!bootloader) {
        printf("Failed to read aboot image\n");
        goto out;
    }

    bl_code = bootloader->code_ptr;
    num_bytes = bootloader->code_size;

    bl_crc = crc32(bl_code, num_bytes);

    image = boot_image_read(argv[3]);
    if(!image) {
        printf("Failed to read patched image\n");
        goto out;
    }

    image_kernel = image->kernel_ptr;
    num_bytes = image->kernel_size;

    if(num_bytes < 8
            || memcmp(image_kernel, boot_magic, 3)
            || image_kernel[3] < 1 || image_kernel[3] > 2) {
        printf("Not a valid patched image\n");
        goto out;
    }

    image_crc = le_uint32_read(image_kernel, 4);

    if(image_crc != bl_crc) {
        printf("Patched image does not match bootloader\n");
        goto out;
    }

    printf("Patched image matches bootloader\n");
    ret = 0;
out:
    if(bootloader) {
        aboot_image_delete(bootloader);
    }
    if(image) {
        boot_image_delete(image);
    }
    return ret;
}
