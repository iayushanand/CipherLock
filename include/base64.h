#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdint.h>

char *base64_encode(const uint8_t *data, size_t input_len);

uint8_t *base64_decode(
    const char *data,
    size_t *output_len
);

#endif