#include "cmd_patch.h"
#include "config.h"
#include "boot_image.h"
#include "aboot_image.h"
#include "crc.h"
#include "asm.h"
#include "little_endian.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

int cmd_patch_main(int argc, char *argv[]) {
    int ret = -2;
    int write_ret = 0;
    aboot_image *bootloader = NULL;
    bootloader_config *config = NULL;
    boot_image *input = NULL;
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

    bl_crc = crc32(bl_code, bl_code_len);
    for(size_t i = 0; i < num_configs; i++) {
        if(configs[i].code_crc == bl_crc) {
            config = &configs[i];
            printf("Supported bootloader found: %s\n", config->name);
            break;
        }
    }
    if(!config) {
        printf("Unsupported bootloader\n");
        goto out;
    }

    input = boot_image_read(argv[3]);
    if(!input) {
        printf("Failed to open original image\n");
        goto out;
    }

    if(input->kernel_size >= 8
            && !memcmp(input->kernel_ptr, boot_magic, 3)
            && input->kernel_ptr[3] >= 1
            && input->kernel_ptr[3] <= 2) {
        printf("Original image already patched\n");
        goto out;
    }

    output = boot_image_new();
    if(!output) {
        printf("Failed to allocate memory for output image\n");
        goto out;
    }

    image_kernel = boot_image_to_bytes(input, &image_kernel_len);
    if(!image_kernel || image_kernel_len < 8) {
        printf("Failed to embed original boot image\n");
        goto out;
    }
    image_kernel[3] = 1;
    le_uint32_write(bl_crc, image_kernel, 4);

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
    if(input) {
        boot_image_delete(input);
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
