#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cipher.h"
#include "decrypt.h"
#include "base64.h"

void decrypt_text(void)
{
    char input[8192];
    char password[64];

    printf("Enter encrypted text:\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    /* Temporary key generation.
       Later this will be replaced with SHA-256. */
    uint8_t key[32] = {0};

    size_t password_len = strlen(password);

    if (password_len > 32)
        password_len = 32;

    memcpy(key, password, password_len);

    /* Temporary IV.
       Later we'll read this from the encrypted data. */
    uint8_t iv[16] = {0};

    uint8_t *ciphertext = NULL;
    size_t ciphertext_len = 0;

    ciphertext = base64_decode(input, &ciphertext_len);

    if (ciphertext == NULL)
    {
        printf("Invalid Base64 input.\n");
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