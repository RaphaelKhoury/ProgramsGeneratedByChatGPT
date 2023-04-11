#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include <cstring>

// Function to generate a random key
void generateRandomKey(unsigned char *key, int keyLength) {
    RAND_bytes(key, keyLength);
}

// Function to derive a key from a password and a salt using PBKDF2
void deriveKey(unsigned char *key, int keyLength, const char *password, const unsigned char *salt, int saltLength, int iterations) {
    PKCS5_PBKDF2_HMAC(password, strlen(password), salt, saltLength, iterations, EVP_sha256(), keyLength, key);
}

int main() {
    const unsigned char plaintext[] = "Hello World";
    const unsigned char iv[] = "initialvector123";

    // Generate a random 256-bit master key
    const int masterKeyLength = 32; // 256-bit key
    unsigned char masterKey[masterKeyLength];
    generateRandomKey(masterKey, masterKeyLength);

    // Derive three unique 128-bit keys using PBKDF2
    const int keyLength = 16; // 128-bit key
    unsigned char johnKey[keyLength];
    unsigned char mikeKey[keyLength];
    unsigned char timKey[keyLength];

    const char *password = "mysecretpassword";
    const int saltLength = 8;
    unsigned char salt[saltLength];
    generateRandomKey(salt, saltLength);

    const int iterations = 10000;

    deriveKey(johnKey, keyLength, password, salt, saltLength, iterations);
    deriveKey(mikeKey, keyLength, password, salt, saltLength, iterations);
    deriveKey(timKey, keyLength, password, salt, saltLength, iterations);

    // Encrypt the plaintext message using AES-GCM with the master key
    unsigned char ciphertext[AES_BLOCK_SIZE];
    memset(ciphertext, 0, AES_BLOCK_SIZE);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL);

    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, sizeof(plaintext));
    int ciphertextLength = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertextLength += len;

    unsigned char tag[EVP_GCM_TLS_TAG_LEN];
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_GET_TAG, EVP_GCM_TLS_TAG_LEN, tag);