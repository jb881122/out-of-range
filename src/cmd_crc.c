#include "cmd_crc.h"
#include "aboot_image.h"
#include "crc.h"

#include <stdio.h>
#include <stddef.h>

int cmd_crc_main(int argc, char *argv[]) {
    int ret = -2;
    aboot_image *image = NULL;
    char *image_code = NULL;
    size_t num_bytes = 0;
    uint32_t code_crc = 0;

    if(argc != 3) {
        printf("Wrong number of arguments\n");
        goto out;
    }

    ret = -1;

    image = aboot_image_read(argv[2]);
    if(!image) {
        printf("Failed to read aboot image\n");
        goto out;
    }

    image_code = image->code_ptr;
    num_bytes = image->code_size;

    code_crc = crc32(image_code, num_bytes);
    printf("0x%08X\n", code_crc);

    ret = 0;
out:
    if(image) {
        aboot_image_delete(image);
    }
    return ret;
}
