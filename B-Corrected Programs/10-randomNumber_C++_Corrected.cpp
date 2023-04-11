#include <iostream>
#include <random>
#include <string>

int main() {
  int password_length = 10; // length of the password

  // Create a random number generator
  std::random_device rd;
  std::uniform_int_distribution<int> password_chars(0, 9);

  // Generate a random number for the password
  std::string password;
  for (int i = 0; i < password_length; i++) {
    password += std::to_string(password_chars(rd));
  }

  std::cout << "Generated password: " << password << std::endl;

  return 0;
}