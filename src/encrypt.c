#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cipher.h"
#include "encrypt.h"
#include "base64.h"
#include "keygen.h"
#include "random.h"
#include "file.h"

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

    uint8_t iv[16];

    if (random_bytes(iv, sizeof(iv)) != 0)
    {
        printf("Failed to generate IV.\n");
        return;
    }

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

    size_t final_len = 16 + encrypted_len;

    uint8_t *final = malloc(final_len);

    if (final == NULL)
    {
        printf("Memory allocation failed.\n");
        free(encrypted);
        return;
    }

    memcpy(final, iv, 16);
    memcpy(final + 16, encrypted, encrypted_len);

    char *encoded = base64_encode(final, final_len);

    if (encoded == NULL)
    {
        printf("Base64 encoding failed.\n");
        free(final);
        free(encrypted);
        return;
    }

    printf("\nEncrypted Text:\n%s\n", encoded);

    free(encoded);
    free(final);
    free(encrypted);
}


void encrypt_file(const char *filename)
{
    uint8_t *buffer = NULL;
    size_t buffer_len = 0;

    if (read_file(filename, &buffer, &buffer_len) != 0)
    {
        printf("Failed to read file.\n");
        return;
    }

    char password[64];

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    uint8_t key[32];
    derive_key(password, key);

    uint8_t iv[16];

    if (random_bytes(iv, sizeof(iv)) != 0)
    {
        printf("Failed to generate IV.\n");
        free(buffer);
        return;
    }

    uint8_t *encrypted = NULL;
    size_t encrypted_len = 0;

    if (encrypt_buffer(
            buffer,
            buffer_len,
            key,
            iv,
            &encrypted,
            &encrypted_len) != 0)
    {
        printf("Encryption failed.\n");
        free(buffer);
        return;
    }

    size_t final_len = 16 + encrypted_len;

    uint8_t *final = malloc(final_len);

    if (final == NULL)
    {
        printf("Memory allocation failed.\n");
        free(buffer);
        free(encrypted);
        return;
    }

    memcpy(final, iv, 16);
    memcpy(final + 16, encrypted, encrypted_len);

    char output[1024];
    snprintf(output, sizeof(output), "%s.clck", filename);

    if (write_file(output, final, final_len) != 0)
    {
        printf("Failed to write encrypted file.\n");
    }
    else
    {
        printf("Encrypted file written to %s\n", output);
    }

    free(buffer);
    free(encrypted);
    free(final);
}