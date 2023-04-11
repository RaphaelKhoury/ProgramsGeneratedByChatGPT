#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>

int main() {
  std::string password = "secret";
  std::string key = "mykey";
  std::string encrypted;

  CryptoPP::AES::Encryption aesEncryption(reinterpret_cast<const byte *>(key.data()), key.size());
  CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, reinterpret_cast<const byte *>(key.data()));

  CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(encrypted));
  stfEncryptor.Put(reinterpret_cast<const byte *>(password.data()), password.size());
  stfEncryptor.MessageEnd();

  std::cout << "Encrypted password: " << encrypted << std::endl;

  return 0;
}