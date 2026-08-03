#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cipher.h"
#include "encrypt.h"
#include "base64.h"

void encrypt_text(void)
{
    char text[1024];
    char password[64];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    uint8_t key[32];
    derive_key(password, key);

    /* Temporary IV.
       Later this will be randomly generated. */
    uint8_t iv[16] = {0};

    uint8_t *encrypted = NULL;
    size_t encrypted_len = 0;

    if (encrypt_buffer(
            (const uint8_t *)text,
            strlen(text),
            key,
            iv,
            &encrypted,
            &encrypted_len) != 0)
    {
        printf("Encryption failed.\n");
        return;
    }

    char *encoded = base64_encode(encrypted, encrypted_len);

    if (encoded == NULL)
    {
        printf("Base64 encoding failed.\n");
        free(encrypted);
        return;
    }

    printf("\nEncrypted Text:\n%s\n", encoded);

    free(encoded);
    free(encrypted);
}

void encrypt_file(const char *filename)
{
    printf("File encryption is not implemented yet.\n");
    printf("Target file: %s\n", filename);
}