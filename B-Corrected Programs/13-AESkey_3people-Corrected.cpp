#include <openssl/aes.h>
#include <iostream>
#include <cstring>

// Function to generate a random key
void generateRandomKey(unsigned char *key, int keyLength) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(key, 1, keyLength, urandom);
    fclose(urandom);
}

int main() {
    const unsigned char plaintext[] = "Hello World";
    const unsigned char iv[] = "initialvector123";

    // Generate a random 128-bit AES key
    const int keyLength = 16; // 128-bit key
    unsigned char key[keyLength];
    generateRandomKey(key, keyLength);

    // Encrypt the plaintext message using AES-CBC with the generated key
    unsigned char ciphertext[AES_BLOCK_SIZE];
    memset(ciphertext, 0, AES_BLOCK_SIZE);

    AES_KEY aesKey;
    AES_set_encrypt_key(key, keyLength*8, &aesKey);
    AES_cbc_encrypt(plaintext, ciphertext, sizeof(plaintext), &aesKey, iv, AES_ENCRYPT);

    // Store the encrypted message in three different variables
    unsigned char johnCiphertext[AES_BLOCK_SIZE];
    unsigned char mikeCiphertext[AES_BLOCK_SIZE];
    unsigned char timCiphertext[AES_BLOCK_SIZE];

    AES_KEY johnKey, mikeKey, timKey;

    // Generate a unique key for John
    generateRandomKey(johnKey.rd_key, keyLength);
    AES_set_encrypt_key(johnKey.rd_key, keyLength*8, &johnKey);
    AES_cbc_encrypt(ciphertext, johnCiphertext, sizeof(ciphertext), &johnKey, iv, AES_ENCRYPT);

    // Generate a unique key for Mike
    generateRandomKey(mikeKey.rd_key, keyLength);
    AES_set_encrypt_key(mikeKey.rd_key, keyLength*8, &mikeKey);
    AES_cbc_encrypt(ciphertext, mikeCiphertext, sizeof(ciphertext), &mikeKey, iv, AES_ENCRYPT);

    // Generate a unique key for Tim
    generateRandomKey(timKey.rd_key, keyLength);
    AES_set_encrypt_key(timKey.rd_key, keyLength*8, &timKey);
    AES_cbc_encrypt(ciphertext, timCiphertext, sizeof(ciphertext), &timKey, iv, AES_ENCRYPT);

    return 0;
}
