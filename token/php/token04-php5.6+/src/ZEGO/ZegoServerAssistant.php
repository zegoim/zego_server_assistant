<?php
namespace ZEGO;

class ZegoServerAssistant {
    
    private static function makeNonce(){
        $nonce = rand();
        return $nonce;
    }

    private static function makeRandomIv($number = 16){
        $str = "0123456789abcdefghijklmnopqrstuvwxyz";
        
        $result = [];
        $strLen = strlen($str);
        for ($i = 0; $i < $number; $i++ ){
            $result[] = $str[rand(0,$strLen-1)];
        }
        return implode('',$result);
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
    public static function generateToken04($appId, $userId, $secret, $effectiveTimeInSeconds, $payload){
        $assistantToken = new ZegoAssistantToken();

        $assistantToken->code = ZegoErrorCodes::success;

        if ( $appId == 0 ) {
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

        $forTestNoce = -626114709072274507;//9223372036854775807
        $forTestCreateTime = 1619769776;
        $forTestIv = "exn62lbokoa8n8jp";
    
        //demo
        //$forTestNoce = 9022377734291506982;
        //$forTestCreateTime = 1619663663;
        //$forTestIv = "forkislbyn0u28qw";
    
        $testMode = false;
    
        $timestamp = $testMode ? $forTestCreateTime : time();//-for test +3600 = 1619667263
    
        $nonce = $testMode ? $forTestNoce : self::makeNonce();
        $data = [
            'app_id'   => $appId,
            'user_id'  => $userId,
            'nonce'    => $nonce,
            'ctime'    => $timestamp,
            'expire'   => $timestamp + $effectiveTimeInSeconds,
            'payload'  => $payload
        ];
    
        $cipher = 'aes-128-cbc';
        
        $plaintext = json_encode($data,JSON_BIGINT_AS_STRING);
    
        switch($keyLen){
            case 16:
                $cipher = 'aes-128-cbc';
            break;
            
            case 24:
                $cipher = 'aes-192-cbc';
            break;
    
            case 32:
                $cipher = 'aes-256-cbc';
            break;
    
            default:
                throw new Exception('secret length does not supported!');
            break;
        }
        
        //$ivlen = openssl_cipher_iv_length($cipher);
        //$iv    = openssl_random_pseudo_bytes($ivlen);
    
        $iv = $testMode ? $forTestIv : self::makeRandomIv();
    
        $encrypted = openssl_encrypt($plaintext, $cipher, $secret, OPENSSL_RAW_DATA, $iv);
    
        //64位有符号整型时间戳-BigEndian + 16位无符号整型iv字节长度计数-BigEndian + iv字符串 + 16位无符号整型aes加密后字符串字节长度计数-BigEndian + aes加密后字符串
        $packData = [
            //$data['expire_time'],
            strlen($iv),
            $iv,
            strlen($encrypted),
            $encrypted
        ];
    
        //print_r($packData);
    
        //$binary = pack('q',$data['expire_time']);//q 有符号长长整型(64位，主机字节序)
        $binary = pack('J',$data['expire']);//J 无符号长长整型(64位，大端字节序)
        $binary .= pack('na*na*', ...$packData);
    
        //"03"字符串 + base64编码binary为字符串
        //print_r(unpack('qq/nn/a*a',$binary));

        $assistantToken->token = '04'.base64_encode($binary);
        return $assistantToken;
    }
}