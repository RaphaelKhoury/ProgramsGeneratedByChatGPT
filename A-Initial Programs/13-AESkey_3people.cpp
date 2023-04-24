#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>
#include <string>
#include <vector>

// The key used for AES encryption. This should be kept secret.
std::vector<unsigned char> key = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

// The initialization vector used for AES encryption.
std::vector<unsigned char> iv = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

// Function to encrypt a given string using AES and return the ciphertext.
std::vector<unsigned char> aes_encrypt(const std::string& plaintext)
{
    // Create a buffer to hold the ciphertext.
    std::vector<unsigned char> ciphertext(plaintext.size() + AES_BLOCK_SIZE);

    // Create an AES encryption context.
    AES_KEY aes_key;
    AES_set_encrypt_key(key.data(), 128, &aes_key);

    // Encrypt the plaintext using AES in CBC mode.
    AES_cbc_encrypt((const unsigned char*) plaintext.data(), ciphertext.data(), plaintext.size(), &aes_key, iv.data(), AES_ENCRYPT);

    return ciphertext;
}

int main()
{
    // Get the plaintext to encrypt.
    std::string plaintext = "Hello, world!";

    // Encrypt the plaintext using AES.
    std::vector<unsigned char> ciphertext = aes_encrypt(plaintext);

    // Send the ciphertext to three different persons.
    // Here, we are just printing the ciphertext to the console.
    std::cout << "Ciphertext 1: " << std::hex;
    for (auto c : ciphertext) {
        std::cout << (int) c << " ";
    }
    std::cout << std::dec << std::endl;

    std::cout << "Ciphertext 2: " << std::hex;
    for (auto c : ciphertext) {
        std::cout << (int) c << " ";
    }
    std::cout << std::dec << std::endl;

    std::cout << "Ciphertext 3: " << std::hex;
    for (auto c : ciphertext) {
        std::cout << (int) c << " ";
    }
    std::cout << std::dec << std::endl;

    return 0;
}
