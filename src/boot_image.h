#ifndef _BOOT_IMAGE_H
#define _BOOT_IMAGE_H

#include <stdint.h>
#include <stddef.h>

/* Note: This does not contain all information in a boot image.
     If any fields are missing, they will be preserved in existing
     images and blank or 0 in new images */
typedef struct {
    char magic[8];
    uint32_t kernel_addr;
    uint32_t ramdisk_size_display;
    uint32_t ramdisk_addr;
    uint32_t second_addr;
    uint32_t tags_addr;

    uint32_t kernel_size;
    char *kernel_ptr;
    uint32_t ramdisk_size;
    char *ramdisk_ptr;
    uint32_t second_size;
    char *second_ptr;
    uint32_t dt_size;
    char *dt_ptr;

    char *_buffer;
    size_t _buf_len;
    int _kernel_ptr_separate;
    int _ramdisk_ptr_separate;
} boot_image;

uint32_t round_up_page(uint32_t offset);

boot_image *boot_image_new(void);
boot_image *boot_image_read(char *file_name);

int boot_image_set_kernel(char *kernel, size_t num_bytes, boot_image *image);
int boot_image_set_ramdisk(char *ramdisk, size_t num_bytes, boot_image *image);

char *boot_image_to_bytes(boot_image *image, size_t *len);
int boot_image_write(char *file_name, boot_image *image);

void boot_image_delete(boot_image *image);

extern char boot_magic[];
extern size_t boot_magic_len;

#endif
