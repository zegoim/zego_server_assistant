package im.zego.serverassistant.sample;

import im.zego.serverassistant.utils.TokenServerAssistant;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Base64;

//
// 权限认证 token 生成示例，使用前需联系即构技术支持开通功能
//

public class Token04ForRtcRoomSample {
    public static void main(String[] args) {
        long appId = 1222222222L;    // 请替换为你的 appId，从即构控制台获取
        String serverSecret = "12345678900987654321123456789012";  // 请替换为你的 serverSecret，从即构控制台获取，
        String userId = "test_user";    // 请替换为用户的 userID，同一 appId 下全网唯一
        int effectiveTimeInSeconds = 300;   // 有效时间，单位：秒

        JSONObject payloadData = new JSONObject();
        payloadData.put("room_id", "demo"); // 房间id，限制用户只能登录特定房间
        JSONObject privilege = new JSONObject();
        //登录房间权限 TokenServerAssistant.PrivilegeEnable 代表允许，TokenServerAssistant.PrivilegeDisable 代表不允许
        //此处代表允许登录房间
        privilege.put(TokenServerAssistant.PrivilegeKeyLogin, TokenServerAssistant.PrivilegeEnable);

        //是否允许推流 TokenServerAssistant.PrivilegeEnable 代表允许，TokenServerAssistant.PrivilegeDisable 代表不允许
        //此处代表不允许推流
        privilege.put(TokenServerAssistant.PrivilegeKeyPublish, TokenServerAssistant.PrivilegeDisable);
        payloadData.put("privilege", privilege);
        payloadData.put("stream_id_list", null);
        String payload = payloadData.toJSONString();

        TokenServerAssistant.VERBOSE = false;    // 调试时，置为 true, 可在控制台输出更多信息；正式运行时，最好置为 false
        TokenServerAssistant.TokenInfo token = TokenServerAssistant.generateToken04(appId,  userId, serverSecret, effectiveTimeInSeconds, payload);
        System.out.println(token.data);

        if (token.error == null || token.error.code == TokenServerAssistant.ErrorCode.SUCCESS) {
            System.out.println("\r\ndecrypt the token ...");
            decryptToken(token.data, serverSecret);
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
