<?php
require_once '../auto_loader.php';
use ZEGO\ZegoServerAssistant;
use ZEGO\ZegoErrorCodes;

//
// 基础鉴权 token 生成示例
//

// 请将 appID 修改为你的 appId，appid 为 数字
// 举例：1234567890
$appId = 1234567890;

// 请将 serverSecret 修改为你的 serverSecret，serverSecret 为 string
// 举例：'fa94dd0f974cf2e293728a526b028271'
$serverSecret = '';

// 请将 userId 修改为用户的 userId
$userId = 'user1';
//生成基础鉴权 token时，payload 要设为空字符串
$payload = ''; 
// 3600 为 token 过期时间，单位：秒
$token = ZegoServerAssistant::generateToken04($appId, $userId, $serverSecret, 3600, $payload);
if( $token->code == ZegoErrorCodes::success ){
  #...
}
print_r($token);

//demo
//3AAAAAGCKKT8AEGZvcmtpc2xieW4wdTI4cXcAoPBuvYE1pAu6k+I9aVF4ooQFkG60sNBVZd8quE2Y/lIgkr60HZT5nP1fUgYABO+wpdT7EOJi00k1oycbtpP3E4wsOgAU11gyPSkBVyJ3V4i2nma8v9IPuH5r9WOVSqsngwWDAlBVxjVO14cWyfGc3UDynsALk+qd9Rk8PVrhWTNWpqZxCsUDyk79omSC4wI4CY/wLmiM+AN+wcL9ohGUNbo=
