#ifndef FILE_H
#define FILE_H

#include <stddef.h>
#include <stdint.h>

int read_file(
    const char *filename,
    uint8_t **buffer,
    size_t *length
);

int write_file(
    const char *filename,
    const uint8_t *buffer,
    size_t length
);

#endif