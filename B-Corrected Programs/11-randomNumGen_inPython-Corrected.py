import os
import string

def generate_password(length):
    chars = string.digits
    password = ''.join(chars[byte % len(chars)] for byte in os.urandom(length))
    return password

password_length = 10
password = generate_password(password_length)
print("Generated password:", password)