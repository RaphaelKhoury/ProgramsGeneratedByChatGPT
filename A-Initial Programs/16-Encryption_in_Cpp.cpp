#include <iostream>
#include <string>
#include <bcrypto/aes.h>

int main() {
  std::string password = "secret";
  std::string key = "mykey";
  std::string encrypted;

  bcrypto::AES aes;
  aes.set_key(reinterpret_cast<const bcrypto::byte *>(key.data()), key.size());
  aes.encrypt(reinterpret_cast<const bcrypto::byte *>(password.data()), password.size(), encrypted);

  std::cout << "Encrypted password: " << encrypted << std::endl;

  return 0;
}