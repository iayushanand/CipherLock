#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aes.h"
#include "cipher.h"


void print_hex(const uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%02X ", data[i]);

    printf("\n");
}

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
    return 0;
}