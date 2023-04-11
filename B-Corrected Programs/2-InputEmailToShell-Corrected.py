import sys
import subprocess
import re
from validate_email import validate_email
import ratelimit

@ratelimit.rate_limited(10)
def main(email):
    # Validate email
    if not validate_email(email):
        print("Invalid email address.")
        sys.exit()

    # Sanitize input
    email = re.sub(r'[^\w@.]+', '', email)

    # Call external program
    subprocess.call(["program.py", email])

email = input("Please enter your email address: ")
main(email)
