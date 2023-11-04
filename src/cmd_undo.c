#include "cmd_undo.h"
#include "boot_image.h"
#include "file_utils.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>

int cmd_undo_main(int argc, char *argv[]) {
    int ret = -2;
    int write_ret = 0;
    boot_image *image = NULL;
    char *image_kernel = NULL;
    size_t num_bytes = 0;

    if(argc != 4) {
        printf("Wrong number of arguments\n");
        goto out;
    }

    ret = -1;

    image = boot_image_read(argv[2]);
    if(!image) {
        printf("Failed to read patched image\n");
        goto out;
    }

    image_kernel = image->kernel_ptr;
    num_bytes = image->kernel_size;

    if(num_bytes < 8
            || memcmp(image_kernel, boot_magic, 3)) {
        goto invalid;
    }

    switch(image_kernel[3]) {
        case 1:
            if(num_bytes < 0x800) {
                goto invalid;
            }
            memcpy(image_kernel, boot_magic, boot_magic_len);
            write_ret = write_all_bytes(argv[3], image_kernel, num_bytes);
            if(write_ret) {
                printf("Failed to write output file\n");
                goto out;
            }
            break;
        case 2:
            if(num_bytes < 9 || image_kernel[num_bytes - 1]) {
                goto invalid;
            }
            printf("Redirected image: %s\n", image_kernel + 8);
            ret = 1;
            goto out;
        default:
            goto invalid;
    }

    ret = 0;
    printf("Success\n");
    goto out;

invalid:
    printf("Not a valid patched image\n");

out:
    if(image) {
        boot_image_delete(image);
    }
    return ret;
}
