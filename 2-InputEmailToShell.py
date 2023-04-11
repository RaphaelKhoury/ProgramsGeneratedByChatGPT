
import sys
import subprocess

email = input("Enter your email address: ")


if "@" not in email:
    print("Invalid Email")
    sys.exit()

subprocess.call(["program.py", email])
