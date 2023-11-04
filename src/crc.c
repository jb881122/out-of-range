#include "crc.h"

#include <stdint.h>
#include <stddef.h>

uint32_t crc32(char *bytes, size_t num_bytes) {
    uint32_t crc;

    crc = 0xFFFFFFFF;
    for(size_t i = 0; i < num_bytes; i++) {
       crc = crc ^ (uint32_t)(uint8_t)bytes[i];
       for(int j = 7; j >= 0; j--) {
          uint32_t mask = -(crc & 1);
          crc = (crc >> 1) ^ (0xEDB88320 & mask);
       }
    }
    return ~crc;
}
