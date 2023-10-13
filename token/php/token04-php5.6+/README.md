[toc]
# 1. 安装
## 方式一(推荐)：composer 官方源packagist安装
执行`composer require zegoim/server_assistant:0.0.1`进行安装使用

## 方式二(推荐)：composer repositories path类型安装
将`token/php`目录下的
主体目录结构：
```
.
├── composer.json
├── composer.lock
├── packages
│   └── zego_server_assistant
└── src
```

composer.json添加path类型的仓库
```json
{
//...
    "repositories": [
        {
            "type": "path",
            "url": "./packages/zego_server_assistant"
        }
    ]
//...
}

```

执行`composer require zegoim/server_assistant:0.0.1`进行安装。

## 方式三：Composer Autoload，即使用composer的PSR-4自动加载机制实现加载

1. 拷贝文件包至项目根目录下的某个目录中，例如这里以`/my_project/zego`目录为例，其中`/my_project/`为项目根目录
2. `vim /my_project/composer.json`加入`psr-4`自动加载配置
```json
{
  ...
  "autoload": {
    "psr-4": {
      "ZEGO\\": "zego/src/ZEGO"
    }
  }
  ...
}
```
1. 执行 `composer dump-autoload` 或 `composer dump-autoload -o`（生产环境适用） 或 `composer update` 命令，生成自动加载文件



## 方式四：Symfony Class Auto Loader 注册自动加载，适合在未使用composer的项目中使用此方式

1. 拷贝文件包至项目根目录下的某个目录中，例如这里以`/my_project/zego`目录为例，其中`/my_project/`为项目根目录

使用时先引入自动加载器
```php
require_once 'zego/auto_loader.php';
```

# 2. 使用
### 普通token 生成demo
- 在`/my_project/xxx.php`文件中使用
- 普通token用于服务接口的简单权限验证的场景，payload字段可传空
```php
require 'vendor/autoload.php';
use ZEGO\ZegoServerAssistant;
use ZEGO\ZegoErrorCodes;

$appId = 1;
$userId = 'demo';
$secret = 'fa94dd0f974cf2e293728a526b028271';
$payload = '';
$token = ZegoServerAssistant::generateToken04($appId,$userId,$secret,3600,$payload);
if( $token->code == ZegoErrorCodes::success ){
  print_r($token->token);
}
```

### 强验证token 生成demo
- 在`/my_project/xxx.php`文件中使用
- 强验证token用于对房间登录/推拉流权限需要进行强验证的场景，payload字段需要按照规格生成
```php
require 'vendor/autoload.php';
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
  print_r($token);
}
```



# 3. 错误码说明

```php
namespace ZEGO;

class ZegoErrorCodes{
    const success                       = 0;  // 获取鉴权 token 成功
    const appIDInvalid                  = 1;  // 调用方法时传入 appID 参数错误
    const userIDInvalid                 = 3;  // 调用方法时传入 userID 参数错误
    const secretInvalid                 = 5;  // 调用方法时传入 secret 参数错误
    const effectiveTimeInSecondsInvalid = 6;  // 调用方法时传入 effectiveTimeInSeconds 参数错误
}
```


# 4. generateToken04 参数及返回值说明

```php
    /**
     * 根据所提供的参数列表生成用于与即构服务端通信的鉴权
     *
     * @param integer $appId Zego派发的数字ID, 各个开发者的唯一标识
     * @param string $userId 用户 ID
     * @param string $secret 由即构提供的与 appId 对应的密钥，请妥善保管，切勿外泄
     * @param integer $effectiveTimeInSeconds token 的有效时长，单位：秒
     * @param string $payload 业务扩展字段，json串
     * @return ZegoAssistantToken 返回 token 内容，值为ZEGO\ZegoAssistantToken对象，在使用前，请检查对象code属性是否为 ZEGO\ZegoErrorCodes::success。实际 token 内容保存在 token 属性中
     */
    public static function generateToken04(int $appId, string $userId, string $secret, int $effectiveTimeInSeconds, string $payload )


```

返回值为`ZEGO\ZegoAssistantToken`对象：
```php

namespace ZEGO;

class ZegoAssistantToken{
    public $code;
    public $message = '';
    public $token;
}
```