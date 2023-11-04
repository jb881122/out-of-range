#ifndef _FILE_UTILS_H
#define _FILE_UTILS_H

#include <stddef.h>

char *read_all_bytes(char *file_name, size_t *bytes_read);
int write_all_bytes(char *file_name, char *bytes, size_t num_bytes);

#endif
