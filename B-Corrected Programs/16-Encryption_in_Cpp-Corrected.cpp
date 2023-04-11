#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Encrypt a plaintext string using AES-256 CBC mode
vector<uint8_t> encrypt(string plaintext, string key, string iv) {
    // Create an encryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (ctx == nullptr) {
        throw runtime_error("Failed to create encryption context");
    }

    // Initialize the encryption operation
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr,
                           reinterpret_cast<const uint8_t *>(key.c_str()),
                           reinterpret_cast<const uint8_t *>(iv.c_str())) != 1) {
        throw runtime_error("Failed to initialize encryption operation");
    }

    // Generate a random initialization vector (IV) if one wasn't provided
    if (iv.empty()) {
        uint8_t iv_buf[EVP_MAX_IV_LENGTH];
        if (RAND_bytes(iv_buf, EVP_MAX_IV_LENGTH) != 1) {
            throw runtime_error("Failed to generate random IV");
        }
        iv = string(reinterpret_cast<const char *>(iv_buf), EVP_MAX_IV_LENGTH);
    }

    // Pad the plaintext to a multiple of the block size
    size_t block_size = EVP_CIPHER_CTX_block_size(ctx);
    size_t padded_len = plaintext.size() + (block_size - plaintext.size() % block_size);
    string padded_text(padded_len, '\0');
    copy(plaintext.begin(), plaintext.end(), padded_text.begin());
    size_t pad_len = padded_len - plaintext.size();
    fill(padded_text.begin() + plaintext.size(), padded_text.end(), static_cast<char>(pad_len));

    // Allocate space for the ciphertext
    vector<uint8_t> ciphertext(padded_text.size() + EVP_CIPHER_CTX_block_size(ctx));

    // Encrypt the padded plaintext
    int len;
    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len,
                          reinterpret_cast<const uint8_t *>(padded_text.c_str()),
                          static_cast<int>(padded_text.size())) != 1) {
        throw runtime_error("Failed to encrypt plaintext");
    }

    // Finalize the encryption operation
    int final_len;
    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &final_len) != 1) {
        throw runtime_error("Failed to finalize encryption operation");
    }
    len += final_len;

    // Resize the ciphertext vector to the actual size
    ciphertext.resize(len);

    // Clean up the encryption context
    EVP_CIPHER_CTX_free(ctx);

    // Return the ciphertext and IV
    vector<uint8_t> iv_and_ciphertext(iv.size() + ciphertext.size());
    copy(iv.begin(), iv.end(), iv_and_ciphertext.begin());
    copy(ciphertext.begin(), ciphertext.end(), iv_and_ciphertext.begin() + iv.size());
    return iv_and_ciphertext;
}

// Decrypt a ciphertext string using AES-256 CBC mode
string decrypt(const vector<uint8_t>& iv_and_ciphertext, string key) {
    // Extract the IV and ciphertext from the input
    string iv(iv_and_ciphertext.begin(), iv_and_ciphertext.begin() + EVP_MAX_IV_LENGTH);
    string ciphertext(iv_and_ciphertext.begin() + EVP_MAX_IV_LENGTH, iv_and_ciphertext.end());

    // Create a decryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (ctx == nullptr) {
        throw runtime_error("Failed to create decryption context");
    }

    // Initialize the decryption operation
