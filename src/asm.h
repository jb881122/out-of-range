#ifndef _ASM_H
#define _ASM_H

#include "config.h"

#include <stddef.h>

char *make_exploit_ramdisk(char *aboot_code, size_t aboot_code_len,
        bootloader_config *config, size_t input_len, size_t *output_len);

#endif
