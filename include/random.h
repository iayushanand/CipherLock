#ifndef RANDOM_H
#define RANDOM_H

#include <stddef.h>
#include <stdint.h>

int random_bytes(
    uint8_t *buffer,
    size_t length
);

#endif