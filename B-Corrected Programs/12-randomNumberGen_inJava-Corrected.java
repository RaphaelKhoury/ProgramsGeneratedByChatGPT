import java.security.SecureRandom;
import java.util.Random;

public class PasswordGenerator {
  public static void main(String[] args) {
    int passwordLength = 10; // length of the password
    char[] chars = "0123456789".toCharArray(); // set of characters to choose from

    // Create a random number generator
    Random random = new SecureRandom();

    // Generate a random password
    char[] password = new char[passwordLength];
    for (int i = 0; i < password.length; i++) {
      password[i] = chars[random.nextInt(chars.length)];
    }

    System.out.println("Generated password: " + new String(password));
  }
}
