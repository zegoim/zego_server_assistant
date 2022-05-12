<?php
require_once '../auto_loader.php';
use ZEGO\ZegoServerAssistant;
use ZEGO\ZegoErrorCodes;

//
// 权限认证 token 生成示例，使用前需联系即构技术支持开通功能
//

//权限位定义
const PrivilegeKeyLogin   = 1; // 登录的权限
const PrivilegeKeyPublish = 2; // 推流的权限

//权限开关定义
const PrivilegeEnable     = 1; // 开启
const PrivilegeDisable    = 0; // 关闭

// 请将 appID 修改为你的 appId，appid 为 数字
// 举例：1234567890
$appId = 1234567890;

// 请将 serverSecret 修改为你的 serverSecret，serverSecret 为 string
// 举例：'fa94dd0f974cf2e293728a526b028271'
$serverSecret = '';

// 请将 userId 修改为用户的 userId
$userId = 'user1';

$roomId = "room1";

$rtcRoomPayLoad = [
    'room_id' => $roomId, //房间id；用于对接口的房间id进行强验证
    'privilege' => [     //权限位开关列表；用于对接口的操作权限进行强验证
        PrivilegeKeyLogin => PrivilegeEnable, //表示允许登录
        PrivilegeKeyPublish => PrivilegeDisable,//表示不允许推流
    ],
    'stream_id_list' => [] //流列表；用于对接口的流id进行强验证；允许为空，如果为空，则不对流id验证
];

$payload = json_encode($rtcRoomPayLoad);

// 3600 为 token 过期时间，单位：秒
$token = ZegoServerAssistant::generateToken04($appId, $userId, $serverSecret, 3600, $payload);
if( $token->code == ZegoErrorCodes::success ){
  #...
}
print_r($token);

//demo
//3AAAAAGCKKT8AEGZvcmtpc2xieW4wdTI4cXcAoPBuvYE1pAu6k+I9aVF4ooQFkG60sNBVZd8quE2Y/lIgkr60HZT5nP1fUgYABO+wpdT7EOJi00k1oycbtpP3E4wsOgAU11gyPSkBVyJ3V4i2nma8v9IPuH5r9WOVSqsngwWDAlBVxjVO14cWyfGc3UDynsALk+qd9Rk8PVrhWTNWpqZxCsUDyk79omSC4wI4CY/wLmiM+AN+wcL9ohGUNbo=
