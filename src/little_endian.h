#ifndef _LITTLE_ENDIAN_H
#define _LITTLE_ENDIAN_H

#include <stdint.h>
#include <stddef.h>

uint32_t le_uint32_read(char *bytes, size_t offset);
void le_uint16_write(uint16_t to_write, char *bytes, size_t offset);
void le_uint32_write(uint32_t to_write, char *bytes, size_t offset);

#endif
