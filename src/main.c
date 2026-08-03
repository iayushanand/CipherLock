#include <stdio.h>
#include <string.h>

void print_help(void)
{
    printf("CipherLock\n\n");
    printf("Usage:\n");
    printf("  cipherlock encrypt\n");
    printf("  cipherlock decrypt\n");
    printf("  cipherlock fencrypt <file>\n");
    printf("  cipherlock fdecrypt <file>\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_help();
        return 1;
    }

    if (strcmp(argv[1], "encrypt") == 0)
    {
        printf("Encrypt text selected.\n");
    }
    else if (strcmp(argv[1], "decrypt") == 0)
    {
        printf("Decrypt text selected.\n");
    }
    else if (strcmp(argv[1], "fencrypt") == 0)
    {
        if (argc < 3)
        {
            printf("Missing filename.\n");
            return 1;
        }

        printf("Encrypt file: %s\n", argv[2]);
    }
    else if (strcmp(argv[1], "fdecrypt") == 0)
    {
        if (argc < 3)
        {
            printf("Missing filename.\n");
            return 1;
        }

        printf("Decrypt file: %s\n", argv[2]);
    }
    else
    {
        printf("Unknown command.\n\n");
        print_help();
    }

    return 0;
}