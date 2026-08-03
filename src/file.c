#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "file.h"

int read_file(
    const char *filename,
    uint8_t **buffer,
    size_t *length)
{
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL)
        return -1;

    fseek(fp, 0, SEEK_END);

    *length = ftell(fp);

    rewind(fp);

    *buffer = malloc(*length);

    if (*buffer == NULL)
    {
        fclose(fp);
        return -1;
    }

    if (fread(*buffer, 1, *length, fp) != *length)
    {
        free(*buffer);
        fclose(fp);
        return -1;
    }

    fclose(fp);

    return 0;
}

int write_file(
    const char *filename,
    const uint8_t *buffer,
    size_t length)
{
    FILE *fp = fopen(filename, "wb");

    if (fp == NULL)
        return -1;

    if (fwrite(buffer, 1, length, fp) != length)
    {
        fclose(fp);
        return -1;
    }

    fclose(fp);

    return 0;
}