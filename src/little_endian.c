#include "little_endian.h"

#include <stdint.h>
#include <stddef.h>

uint32_t le_uint32_read(char *bytes, size_t offset) {
    uint32_t ret = 0;
    for(size_t i = offset; i < offset + 4; i++) {
        ret >>= 8;
        ret += (uint32_t)(uint8_t)bytes[i] << 24;
    }
    return ret;
}

void le_uint16_write(uint16_t to_write, char *bytes, size_t offset) {
    uint16_t remaining = to_write;
    for(size_t i = offset; i < offset + 2; i++) {
        bytes[i] = (char)(remaining & 0xFF);
        remaining >>= 8;
    }
}

void le_uint32_write(uint32_t to_write, char *bytes, size_t offset) {
    uint32_t remaining = to_write;
    for(size_t i = offset; i < offset + 4; i++) {
        bytes[i] = (char)(remaining & 0xFF);
        remaining >>= 8;
    }
}
