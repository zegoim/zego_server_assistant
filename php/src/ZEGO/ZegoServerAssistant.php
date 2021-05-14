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
    
    public static function generateToken(int $appId, string $roomId, string $userId ,array $privilege ,string $secret ){
        
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
            'app_id' =>      $appId,
            'room_id' =>     $roomId,
            'user_id' =>     $userId,
            'privilege' =>   $privilege,//map[int]int
            'create_time' => $timestamp,
            'expire_time' => $timestamp + 3600,
            'nonce'       => $nonce,
        ];
    
        $cipher = 'aes-128-cbc';
        
        $plaintext = json_encode($data,JSON_BIGINT_AS_STRING);
    
        $keyLen = strlen($secret);
    
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
        $binary = pack('J',$data['expire_time']);//J 无符号长长整型(64位，大端字节序)
        $binary .= pack('na*na*', ...$packData);
    
        //"03"字符串 + base64编码binary为字符串
        //print_r(unpack('qq/nn/a*a',$binary));
    
        return '03'.base64_encode($binary);
    }
}