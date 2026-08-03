# CipherLock

CipherLock is a lightweight command-line encryption utility written in C that securely encrypts and decrypts both text and files using **AES-256-CBC**. It was built to explore low-level cryptography, binary file processing, and secure password-based encryption without relying on heavyweight cryptographic frameworks.

## Features

- AES-256-CBC encryption
- Text encryption and decryption
- File encryption and decryption
- Binary-safe encryption for any file type
- Cross-platform C code (Windows and Linux compatible)

---

## How It Works

CipherLock encrypts data using **AES-256 in CBC mode**. Instead of using the user's password directly as the encryption key, the password is first hashed with **SHA-256**, producing a fixed 256-bit key suitable for AES-256.

Every encryption operation generates a new cryptographically secure **16-byte Initialization Vector (IV)**. The IV is prepended to the encrypted output so it can be extracted automatically during decryption. Since the IV is randomly generated each time, encrypting the same data twice with the same password produces different ciphertext.

For text encryption, the encrypted bytes are encoded using **Base64**, making them easy to display, copy, and paste in a terminal. File encryption stores the encrypted bytes directly without any additional encoding, preserving the binary data efficiently.

During decryption, CipherLock extracts the stored IV, derives the AES key from the provided password using SHA-256, decrypts the ciphertext, removes the PKCS#7 padding, and reconstructs the original plaintext or file.

---

## Usage


<p align="center">
    <img src="https://cdn.ayushanand.com/cipherlock.png" width="400">
</p>


---

## Building

### Windows (MinGW)

```bash
gcc src/main.c src/encrypt.c src/decrypt.c src/cipher.c src/base64.c src/keygen.c src/random.c src/file.c crypto/aes.c crypto/sha256.c -Iinclude -Icrypto -lbcrypt -o cipherlock
```

---

## Dependencies

- **tiny-AES-c** for AES-256 implementation
- **crypto-algorithms** for SHA-256 implementation
- **Windows BCrypt API** for secure random IV generation


---

## License

This project is licensed under the MIT License.