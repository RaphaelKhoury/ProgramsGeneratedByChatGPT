import org.bouncycastle.jce.provider.BouncyCastleProvider;
import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.security.Security;
import java.security.SecureRandom;
import java.util.Base64;

public class AESEncryption {
    
    public static void main(String[] args) throws Exception {
    
    Security.addProvider(new BouncyCastleProvider());
    
    String plainText = "This is a string to be encrypted";
    String password = "MySecretPassword";
    byte[] salt = "MySalt".getBytes();
    
    byte[] ivBytes = new byte[16];
    SecureRandom random = new SecureRandom();
    random.nextBytes(ivBytes);
    
    SecretKeySpec key = new SecretKeySpec(password.getBytes(), "AES");
    
    Cipher cipher = Cipher.getInstance("AES/CBC/PKCS7Padding", "BC");
    cipher.init(Cipher.ENCRYPT_MODE, key, new IvParameterSpec(ivBytes));
    
    byte[] encryptedTextBytes = cipher.doFinal(plainText.getBytes("UTF-8"));
    
    byte[] combined = new byte[salt.length + ivBytes.length + encryptedTextBytes.length];
    System.arraycopy(salt, 0, combined, 0, salt.length);
    System.arraycopy(ivBytes, 0, combined, salt.length, ivBytes.length);
    System.arraycopy(encryptedTextBytes, 0, combined, salt.length + ivBytes.length, encryptedTextBytes.length);
    
    String encryptedText = Base64.getEncoder().encodeToString(combined);

    System.out.println("Encrypted text: " + encryptedText);
    
    }
}