// wrote the base64 encoder / decoder myself bcs i was too lazy to find the lib ;-;

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "base64.h"

static const char encoding_table[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static int decoding_table[256];
static int table_built = 0;

static void build_decoding_table(void)
{
    if (table_built)
        return;

    for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char)encoding_table[i]] = i;

    table_built = 1;
}

char *base64_encode(const uint8_t *data, size_t input_len)
{
    size_t output_len = 4 * ((input_len + 2) / 3);

    char *encoded = malloc(output_len + 1);

    if (!encoded)
        return NULL;

    size_t i = 0;
    size_t j = 0;

    while (i < input_len)
    {
        uint32_t octet_a = i < input_len ? data[i++] : 0;
        uint32_t octet_b = i < input_len ? data[i++] : 0;
        uint32_t octet_c = i < input_len ? data[i++] : 0;

        uint32_t triple =
            (octet_a << 16) |
            (octet_b << 8) |
            octet_c;

        encoded[j++] = encoding_table[(triple >> 18) & 0x3F];
        encoded[j++] = encoding_table[(triple >> 12) & 0x3F];
        encoded[j++] = encoding_table[(triple >> 6) & 0x3F];
        encoded[j++] = encoding_table[triple & 0x3F];
    }

    switch (input_len % 3)
    {
        case 1:
            encoded[output_len - 1] = '=';
            encoded[output_len - 2] = '=';
            break;

        case 2:
            encoded[output_len - 1] = '=';
            break;
    }

    encoded[output_len] = '\0';

    return encoded;
}

uint8_t *base64_decode(
    const char *data,
    size_t *output_len)
{
    build_decoding_table();

    size_t input_len = strlen(data);

    if (input_len % 4 != 0)
        return NULL;

    *output_len = input_len / 4 * 3;

    if (data[input_len - 1] == '=')
        (*output_len)--;

    if (data[input_len - 2] == '=')
        (*output_len)--;

    uint8_t *decoded = malloc(*output_len);

    if (!decoded)
        return NULL;

    size_t i = 0;
    size_t j = 0;

    while (i < input_len)
    {
        uint32_t sextet_a =
            data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]];
        i++;

        uint32_t sextet_b =
            data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]];
        i++;

        uint32_t sextet_c =
            data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]];
        i++;

        uint32_t sextet_d =
            data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]];
        i++;

        uint32_t triple =
            (sextet_a << 18) |
            (sextet_b << 12) |
            (sextet_c << 6) |
            sextet_d;

        if (j < *output_len)
            decoded[j++] = (triple >> 16) & 0xFF;

        if (j < *output_len)
            decoded[j++] = (triple >> 8) & 0xFF;

        if (j < *output_len)
            decoded[j++] = triple & 0xFF;
    }

    return decoded;
}