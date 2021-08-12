package im.zego.serverassistant;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Base64;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;


import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

public class Token04Sample {
    public static void main(String[] args) {
        long appId = 1L;    // 由即构提供
        String secretKey = "12345678900987654321123456789012";  // 由即构提供
        String userId = "test_user";    // 用户 ID，同一 appId 下全网唯一
        int effectiveTimeInSeconds = 300;   // 有效时间，单位：秒

        TokenServerAssistant.VERBOSE = false;    // 调试时，置为 true, 可在控制台输出更多信息；正式运行时，最好置为 false
        TokenServerAssistant.TokenInfo token = TokenServerAssistant.generateToken04(appId,  userId, secretKey, effectiveTimeInSeconds);
        System.out.println(token);

        if (token.error == null || token.error.code == TokenServerAssistant.ErrorCode.SUCCESS) {
            System.out.println("\r\ndecrypt the token ...");
            decryptToken(token.data, secretKey);
        }
    }

    static private void decryptToken(String token, String secretKey) {
        String noVersionToken = token.substring(2);

        byte[] tokenBytes = Base64.getDecoder().decode(noVersionToken.getBytes());
        ByteBuffer buffer = ByteBuffer.wrap(tokenBytes);
        buffer.order(ByteOrder.BIG_ENDIAN);
        long expiredTime = buffer.getLong();
        System.out.println("expiredTime: " + expiredTime);
        int IVLength = buffer.getShort();
        byte[] ivBytes = new byte[IVLength];
        buffer.get(ivBytes);
        int contentLength = buffer.getShort();
        byte[] contentBytes = new byte[contentLength];
        buffer.get(contentBytes);

        try {
            SecretKeySpec key = new SecretKeySpec(secretKey.getBytes(), "AES");
            IvParameterSpec iv = new IvParameterSpec(ivBytes);

            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            cipher.init(Cipher.DECRYPT_MODE, key, iv);

            byte[] rawBytes = cipher.doFinal(contentBytes);
            JSONParser parser = new JSONParser();
            JSONObject json = (JSONObject)parser.parse(new String(rawBytes));
            System.out.println(json);
        } catch (Exception e) {
            System.out.println("decrypt failed: " + e);
        }
    }

}
