<?php
require_once '../auto_loader.php';
use ZEGO\ZegoServerAssistant;
use ZEGO\ZegoErrorCodes;

//权限位定义
const PrivilegeKeyLogin   = 1; // 登录
const PrivilegeKeyPublish = 2; // 推流

//权限开关定义
const PrivilegeEnable     = 1; // 开启
const PrivilegeDisable    = 0; // 关闭

$appId = 1;
$userId = 'demo';
$roomId = "demo";
$secret = 'fa94dd0f974cf2e293728a526b028271';
$rtcRoomPayLoad = [
    'room_id' => $roomId, //房间id；用于对接口的房间id进行强验证
    'privilege' => [     //权限位开关列表；用于对接口的操作权限进行强验证
        PrivilegeKeyLogin => PrivilegeEnable,
        PrivilegeKeyPublish => PrivilegeDisable,
    ],
    'stream_id_list' => [] //流列表；用于对接口的流id进行强验证；允许为空，如果为空，则不对流id验证
];

$payload = json_encode($rtcRoomPayLoad);

$token = ZegoServerAssistant::generateToken04($appId, $userId, $secret, 3600, $payload);
if( $token->code == ZegoErrorCodes::success ){
  #...
}
print_r($token);

//demo
//3AAAAAGCKKT8AEGZvcmtpc2xieW4wdTI4cXcAoPBuvYE1pAu6k+I9aVF4ooQFkG60sNBVZd8quE2Y/lIgkr60HZT5nP1fUgYABO+wpdT7EOJi00k1oycbtpP3E4wsOgAU11gyPSkBVyJ3V4i2nma8v9IPuH5r9WOVSqsngwWDAlBVxjVO14cWyfGc3UDynsALk+qd9Rk8PVrhWTNWpqZxCsUDyk79omSC4wI4CY/wLmiM+AN+wcL9ohGUNbo=
