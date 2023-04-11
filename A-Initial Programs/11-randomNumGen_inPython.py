import random
import string

def generate_password(length):
    chars = string.digits
    password = ''.join(random.choice(chars) for _ in range(length))
    return password

password_length = 10
password = generate_password(password_length)
print("Generated password:", password)
