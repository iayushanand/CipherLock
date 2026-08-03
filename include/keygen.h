#ifndef KEYGEN_H
#define KEYGEN_H

#include <stdint.h>

void derive_key(
    const char *password,
    uint8_t key[32]
);

#endif