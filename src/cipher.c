#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aes.h"
#include "cipher.h"

// instead of printing hex I will instead do base64 bcs thats how most encryption tool works.. let me find a good base64 lib
char *base64_encode(
    const uint8_t *data,
    size_t input_length
);

int base64_decode(
    const char *input,
    uint8_t **output,
    size_t *output_length
);


// mind u its 3 am and I have no idea what I am writing or what I am doign wit my life...
// if this code fails to work I will cry myself to sleep and think about life choices...
// urs truly ~ ayu
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


int encrypt_buffer(
    const uint8_t *input,
    size_t input_len,
    const uint8_t *key,
    const uint8_t *iv,
    uint8_t **output,
    size_t *output_len)
{
    *output_len = pkcs7_pad(input, input_len, output);

    if (*output == NULL || *output_len == 0)
    {
        return -1;
    }

    uint8_t iv_copy[16];
    memcpy(iv_copy, iv, 16);

    struct AES_ctx ctx;

    AES_init_ctx_iv(&ctx, key, iv_copy);

    AES_CBC_encrypt_buffer(&ctx, *output, *output_len);

    return 0;
}



int decrypt_buffer(
    const uint8_t *input,
    size_t input_len,
    const uint8_t *key,
    const uint8_t *iv,
    uint8_t **output,
    size_t *output_len)
{
    *output = malloc(input_len + 1);

    if (*output == NULL)
    {
        return -1;
    }

    memcpy(*output, input, input_len);

    uint8_t iv_copy[16];
    memcpy(iv_copy, iv, 16);

    struct AES_ctx ctx;

    AES_init_ctx_iv(&ctx, key, iv_copy);

    AES_CBC_decrypt_buffer(&ctx, *output, input_len);

    *output_len = pkcs7_unpad(*output, input_len);

    (*output)[*output_len] = '\0';

    return 0;
}



