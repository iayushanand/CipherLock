#include <windows.h>
#include <bcrypt.h>

#include "random.h"

int random_bytes(
    uint8_t *buffer,
    size_t length)
{
    NTSTATUS status = BCryptGenRandom(
        NULL,
        buffer,
        (ULONG)length,
        BCRYPT_USE_SYSTEM_PREFERRED_RNG
    );

    return BCRYPT_SUCCESS(status) ? 0 : -1;
}