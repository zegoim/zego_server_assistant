<?php
namespace ZEGO;

class ZegoServerAssistant
{
    private static function makeNonce()
    {
        $nonce = rand();
        return $nonce;
    }

    private static function makeRandomIv($number = 16)
    {
        $str = "0123456789abcdefghijklmnopqrstuvwxyz";
        
        $result = [];
        $strLen = strlen($str);
        for ($i = 0; $i < $number; $i++) {
            $result[] = $str[rand(0, $strLen-1)];
        }
        return implode('', $result);
    }
    
    /**
     * 根据所提供的参数列表生成用于与即构服务端通信的鉴权
     *
     * @param integer $appId Zego派发的数字ID, 各个开发者的唯一标识
     * @param string $userId 用户 ID
     * @param string $secret 由即构提供的与 appId 对应的密钥，请妥善保管，切勿外泄
     * @param integer $effectiveTimeInSeconds token 的有效时长，单位：秒
     * @param string $payload 业务扩展字段，json串
     * @return ZegoAssistantToken 返回 token 内容，在使用前，请检查 code 字段是否为 ZegoErrorCodes::success。实际 token 内容保存在 token 字段中
     */
    public static function generateToken04($appId, $userId, $secret, $effectiveTimeInSeconds, $payload)
    {
        $assistantToken = new ZegoAssistantToken();

        $assistantToken->code = ZegoErrorCodes::success;

        if ($appId == 0) {
            $assistantToken->code = ZegoErrorCodes::appIDInvalid;
            $assistantToken->message = 'appID invalid';
            return $assistantToken;
        }
        
        if ($userId == "") {
            $assistantToken->code = ZegoErrorCodes::userIDInvalid;
            $assistantToken->message = 'userID invalid';
            return $assistantToken;
        }

        $keyLen = strlen($secret);

        if ($keyLen != 32) {
            $assistantToken->code = ZegoErrorCodes::secretInvalid;
            $assistantToken->message = 'secret must be a 32 byte string';
            return $assistantToken;
        }

        if ($effectiveTimeInSeconds <= 0) {
            $assistantToken->code = ZegoErrorCodes::effectiveTimeInSecondsInvalid;
            $assistantToken->message = 'effectiveTimeInSeconds invalid';
            return $assistantToken;
        }

        
        $tokenInfo = [
            'app_id'   => $appId,
            'user_id'  => $userId,
            'nonce'    => self::makeNonce(),
            'ctime'    => time(),
            'expire'   => time() + $effectiveTimeInSeconds,
            'payload'  => $payload
        ];
        
        // 把 token 信息转成 JSON
        $plaintext = json_encode($tokenInfo, JSON_BIGINT_AS_STRING);

        // 加密
        $cipher = 'aes-256-gcm';
        $iv = self::makeRandomIv(12);
  
        $encrypted = openssl_encrypt($plaintext, $cipher, $secret, OPENSSL_RAW_DATA, $iv, $tag); // 使用 AES-GCM 加密
  
        // 检查加密是否成功
        if ($encrypted === false) {
            $assistantToken->code = ZegoErrorCodes::secretInvalid;
            $assistantToken->message = 'Encryption failed';
            return $assistantToken;
        }
    
        $encrypted .= $tag; // 把 tag 追加到加密数据后面
        // 打包数据
        $binary = pack('J', $tokenInfo['expire']); // 打包过期时间
        $binary .= pack('n', strlen($iv)) . $iv; // 打包 tag 长度和数据
        $binary .= pack('n', strlen($encrypted)) . $encrypted; // 打包加密数据
        $binary .= pack('C', 1); // 打包 AesEncryptModeGCM，假设值为 1

        $assistantToken->token = '04'.base64_encode($binary);
        return $assistantToken;
    }
}
