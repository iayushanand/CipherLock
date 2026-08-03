#ifndef CIPHER_H
#define CIPHER_H

#include <stdint.h>
#include <stddef.h>

void print_hex(const uint8_t *data, size_t len);

size_t pkcs7_pad(
    const uint8_t *input,
    size_t input_len,
    uint8_t **output
);

size_t pkcs7_unpad(
    uint8_t *buffer,
    size_t length
);

int encrypt_buffer(
    const uint8_t *input,
    size_t input_len,
    const uint8_t *key,
    const uint8_t *iv,
    uint8_t **output,
    size_t *output_len
);

int decrypt_buffer(
    const uint8_t *input,
    size_t input_len,
    const uint8_t *key,
    const uint8_t *iv,
    uint8_t **output,
    size_t *output_len
);

int hex_to_bytes(
    const char *hex,
    uint8_t **output,
    size_t *output_len
);

#endif