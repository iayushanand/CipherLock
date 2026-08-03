#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cipher.h"
#include "decrypt.h"
#include "base64.h"
#include "keygen.h"
#include "file.h"

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

    uint8_t key[32];
    derive_key(password, key);

    uint8_t *decoded = NULL;
    size_t decoded_len = 0;

    decoded = base64_decode(input, &decoded_len);

    if (decoded == NULL)
    {
        printf("Invalid Base64 input.\n");
        return;
    }

    if (decoded_len < 16)
    {
        printf("Invalid encrypted data.\n");
        free(decoded);
        return;
    }

    uint8_t iv[16];
    memcpy(iv, decoded, 16);

    uint8_t *ciphertext = decoded + 16;
    size_t ciphertext_len = decoded_len - 16;

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
        free(decoded);
        return;
    }

    printf("\nDecrypted Text:\n%s\n", plaintext);

    free(plaintext);
    free(decoded);
}

void decrypt_file(const char *filename)
{
    uint8_t *buffer = NULL;
    size_t buffer_len = 0;

    if (read_file(filename, &buffer, &buffer_len) != 0)
    {
        printf("Failed to read file.\n");
        return;
    }

    if (buffer_len < 16)
    {
        printf("Invalid encrypted file.\n");
        free(buffer);
        return;
    }

    char password[64];

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    uint8_t key[32];
    derive_key(password, key);

    uint8_t iv[16];
    memcpy(iv, buffer, 16);

    uint8_t *ciphertext = buffer + 16;
    size_t ciphertext_len = buffer_len - 16;

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
        free(buffer);
        return;
    }

    char output[1024];

    strncpy(output, filename, sizeof(output));
    output[sizeof(output) - 1] = '\0';

    char *ext = strrchr(output, '.');

    if (ext != NULL && strcmp(ext, ".clck") == 0)
    {
        *ext = '\0';
    }
    else
    {
        printf("Not a CipherLock file.\n");
        free(buffer);
        free(plaintext);
        return;
    }

    if (write_file(output, plaintext, plaintext_len) != 0)
    {
        printf("Failed to write decrypted file.\n");

        free(buffer);
        free(plaintext);
        return;
    }

    printf("File decrypted successfully.\n");
    printf("Output: %s\n", output);

    free(buffer);
    free(plaintext);
}