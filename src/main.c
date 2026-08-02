#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "aes.h"

void print_hex(const uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%02X ", data[i]);

    printf("\n");
}

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


size_t pkcs7_pad(
    const uint8_t *input,
    size_t input_len,
    uint8_t **output
);

size_t pkcs7_unpad(
    uint8_t *buffer,
    size_t length)
{
    if (length == 0)
        return 0;

    uint8_t padding = buffer[length - 1];

    if (padding > 16)
        return length;

    return length - padding;
}


size_t pkcs7_pad(
    const uint8_t *input,
    size_t input_len,
    uint8_t **output)
{
    const size_t BLOCK_SIZE = 16;

    size_t padding = BLOCK_SIZE - (input_len % BLOCK_SIZE);

    if (padding == 0)
        padding = BLOCK_SIZE;

    size_t output_len = input_len + padding;

    *output = malloc(output_len);

    if (*output == NULL)
        return 0;

    memcpy(*output, input, input_len);

    for (size_t i = input_len; i < output_len; i++)
        (*output)[i] = (uint8_t)padding;

    return output_len;
}

int main(void)
{
    uint8_t key[32] = {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
        0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
        0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F
    };

    uint8_t iv[16] = {
        0x00,0x01,0x02,0x03,
        0x04,0x05,0x06,0x07,
        0x08,0x09,0x0A,0x0B,
        0x0C,0x0D,0x0E,0x0F
    };

    const char *text = "Hello, World! This is me testing stuff...";

    uint8_t *buffer = NULL;

    size_t buffer_len = pkcs7_pad(
        (const uint8_t *)text,
        strlen(text),
        &buffer
    );

    struct AES_ctx ctx;

    printf("Original: %s\n", buffer);

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, buffer, buffer_len);

    printf("Encrypted:\n");
    print_hex(buffer, 16);

    uint8_t iv2[16] = {
        0x00,0x01,0x02,0x03,
        0x04,0x05,0x06,0x07,
        0x08,0x09,0x0A,0x0B,
        0x0C,0x0D,0x0E,0x0F
    };

    AES_init_ctx_iv(&ctx, key, iv2);
    AES_CBC_decrypt_buffer(&ctx, buffer, buffer_len);

    buffer_len = pkcs7_unpad(buffer, buffer_len);

    buffer[buffer_len] = '\0';

    printf("%s\n", buffer);


    return 0;
}