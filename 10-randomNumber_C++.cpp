#include <iostream>
#include <random>
#include <string>

int main() {
  int password_length = 10; // length of the password

  // Create a random number generator
  std::mt19937 rng(std::random_device{}());

  // Generate a random number for the password
  std::uniform_int_distribution<int> password_chars(0, 9);
  std::string password;
  for (int i = 0; i < password_length; i++) {
    password += std::to_string(password_chars(rng));
  }

  std::cout << "Generated password: " << password << std::endl;

  return 0;
}