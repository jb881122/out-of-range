#include "cmd_redirect.h"
#include "config.h"
#include "boot_image.h"
#include "aboot_image.h"
#include "crc.h"
#include "asm.h"
#include "little_endian.h"
#include "bl_check.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

char *make_redirect_binary(char *part_name, uint32_t crc, size_t *output_len) {
    size_t len = 0;
    char *ret = NULL;

    if(output_len) {
        *output_len = 0;
    }

    len = 8 + strlen(part_name) + 1;
    ret = malloc(len);
    if(!ret) {
        goto out;
    }

    memcpy(ret, boot_magic, 3);
    ret[3] = 2;
    le_uint32_write(crc, ret, 4);
    strcpy(ret + 8, part_name);

    if(output_len) {
        *output_len = len;
    }

out:
    return ret;
}

int cmd_redirect_main(int argc, char *argv[]) {
    int ret = -2;
    int write_ret = 0;
    aboot_image *bootloader = NULL;
    bootloader_config *config = NULL;
    boot_image *output = NULL;
    char *bl_code = NULL;
    size_t bl_code_len = 0;
    char *image_kernel = NULL;
    size_t image_kernel_len = 0;
    char *image_ramdisk = NULL;
    size_t image_ramdisk_len = 0;
    uint32_t bl_crc = 0;

    if(argc != 5) {
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
    bl_code_len = bootloader->code_size;

    config = get_config(bl_code, bl_code_len);
    if(!config) {
        goto out;
    }

    output = boot_image_new();
    if(!output) {
        printf("Failed to allocate memory for output image\n");
        goto out;
    }

    bl_crc = crc32(bl_code, bl_code_len);
    image_kernel = make_redirect_binary(argv[3], bl_crc, &image_kernel_len);
    if(!image_kernel) {
        printf("Failed to generate redirect binary\n");
        goto out;
    }

    image_ramdisk = make_exploit_ramdisk(bl_code, bl_code_len, config,
            image_kernel_len, &image_ramdisk_len);
    if(!image_ramdisk) {
        printf("Failed to generate patched aboot code\n");
        goto out;
    }

    if(0x800 + round_up_page(image_kernel_len) + round_up_page(image_ramdisk_len)
            > config->max_boot_img_size) {
        printf("Output image too large\n");
        goto out;
    }

    output->kernel_addr = config->kernel_load_ptr;
    boot_image_set_kernel(image_kernel, image_kernel_len, output);
    output->ramdisk_addr = config->img_base - 0x800;
    boot_image_set_ramdisk(image_ramdisk, image_ramdisk_len, output);
    output->ramdisk_size_display = config->img_end - config->img_base + 0x800;

    write_ret = boot_image_write(argv[4], output);
    if(write_ret) {
        printf("Failed to write output image\n");
        goto out;
    }

    printf("Success\n");
    ret = 0;
out:
    if(bootloader) {
        aboot_image_delete(bootloader);
    }
    if(output) {
        boot_image_delete(output);
    }
    if(image_kernel) {
        free(image_kernel);
    }
    if(image_ramdisk) {
        free(image_ramdisk);
    }
    return ret;
}
