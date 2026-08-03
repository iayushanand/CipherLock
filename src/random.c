#include <windows.h>
#include <bcrypt.h>

#include "random.h"

int random_bytes(
    uint8_t *buffer,
    size_t length)
{
    return BCryptGenRandom(
        NULL,
        buffer,
        (ULONG)length,
        BCRYPT_USE_SYSTEM_PREFERRED_RNG
    ) == STATUS_SUCCESS ? 0 : -1;
}