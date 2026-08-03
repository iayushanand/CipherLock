#include <string.h>

#include "sha256.h"
#include "keygen.h"

void derive_key(
    const char *password,
    uint8_t key[32])
{
    SHA256_CTX ctx;

    sha256_init(&ctx);
    sha256_update(
        &ctx,
        (const uint8_t *)password,
        strlen(password)
    );
    sha256_final(&ctx, key);
}