#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cipher.h"
#include "decrypt.h"

void decrypt_text(void)
{
    char hex[4096];
    char password[64];

    printf("Enter encrypted hex:\n");
    fgets(hex, sizeof(hex), stdin);
    hex[strcspn(hex, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    uint8_t key[32] = {0};

    size_t password_len = strlen(password);

    if (password_len > 32)
        password_len = 32;

    memcpy(key, password, password_len);

    uint8_t iv[16] = {0};

    uint8_t *ciphertext = NULL;
    size_t ciphertext_len = 0;

    if (hex_to_bytes(
            hex,
            &ciphertext,
            &ciphertext_len) != 0)
    {
        printf("Invalid encrypted data.\n");
        return;
    }

    uint8_t *plaintext = NULL;
    size_t plaintext_len = 0;

    if (decrypt_buffer(
            ciphertext,
            ciphertext_len,
            key,
            iv,
            &plaintext,
            &plaintext_len) != 0)
    {
        printf("Decryption failed.\n");
        free(ciphertext);
        return;
    }

    printf("\nDecrypted Text:\n%s\n", plaintext);

    free(ciphertext);
    free(plaintext);
}

void decrypt_file(const char *filename)
{
    printf("File decryption is not implemented yet.\n");
    printf("Target file: %s\n", filename);
}