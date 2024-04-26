#ifndef _BL_CHECK_H
#define _BL_CHECK_H

#include "config.h"

#include <stdint.h>

bootloader_config *get_config(char *bl_code, size_t bl_code_len);

#endif
