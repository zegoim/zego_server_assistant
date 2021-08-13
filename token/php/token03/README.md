#### 安装&使用
##### 方式一(推荐)：Composer Autoload，即使用composer的PSR-4自动加载机制实现加载
**安装**
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
3. 执行 `composer dump-autoload` 或 `composer dump-autoload -o`（生产环境适用） 或 `composer update` 命令，生成自动加载文件

**使用**  
在`/my_project/xxx.php`文件中使用
```php
require 'vendor/autoload.php';
use ZEGO\ZegoServerAssistant;
use ZEGO\ZegoErrorCodes;

$appId = 1;
$roomId = 'demo';
$userId = 'demo';
$secret = 'fa94dd0f974cf2e293728a526b028271';
$token = ZegoServerAssistant::generateToken($appId,$roomId,$userId,["1"=> 1, "2"=>1],$secret,3600);
if( $token->code == ZegoErrorCodes::success ){
  print_r($token->token);
}

```

##### 方式二：Symfony Class Auto Loader 注册自动加载，适合在未使用composer的项目中使用此方式
**安装**
1. 拷贝文件包至项目根目录下的某个目录中，例如这里以`/my_project/zego`目录为例，其中`/my_project/`为项目根目录

**使用**  
在`/my_project/xxx.php`文件中使用
```php
require_once 'zego/auto_loader.php';
use ZEGO\ZegoServerAssistant;
use ZEGO\ZegoErrorCodes;

$appId = 1;
$roomId = 'demo';
$userId = 'demo';
$secret = 'fa94dd0f974cf2e293728a526b028271';
$token = ZegoServerAssistant::generateToken($appId,$roomId,$userId,["1"=> 1, "2"=>1],$secret,3600);
if( $token->code == ZegoErrorCodes::success ){
  print_r($token->token);
}
```

## 错误码说明

```php
namespace ZEGO;

class ZegoErrorCodes{
    const success                       = 0;  // 获取鉴权 token 成功
    const appIDInvalid                  = 1;  // 调用方法时传入 appID 参数错误
    const roomIDInvalid                 = 2;  // 调用方法时传入 roomID 参数错误
    const userIDInvalid                 = 3;  // 调用方法时传入 userID 参数错误
    const privilegeInvalid              = 4;  // 调用方法时传入 privilege 参数错误
    const secretInvalid                 = 5;  // 调用方法时传入 secret 参数错误
    const effectiveTimeInSecondsInvalid = 6;  // 调用方法时传入 effectiveTimeInSeconds 参数错误
}
```


## generateToken 参数及返回值说明

```php
    /**
     * 根据所提供的参数列表生成用于与即构服务端通信的鉴权
     *
     * @param integer $appId Zego派发的数字ID, 各个开发者的唯一标识
     * @param string $roomId 房间 ID
     * @param string $userId 用户 ID
     * @param array $privilege 房间权限
     * @param string $secret 由即构提供的与 appId 对应的密钥，请妥善保管，切勿外泄
     * @param integer $effectiveTimeInSeconds token 的有效时长，单位：秒
     * @return ZegoAssistantToken 返回 token 内容，值为ZEGO\ZegoAssistantToken对象，在使用前，请检查对象code属性是否为 ZEGO\ZegoErrorCodes::success。实际 token 内容保存在 token 属性中
     */
    public static function generateToken(int $appId, string $roomId, string $userId ,array $privilege ,string $secret,int $effectiveTimeInSeconds )


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
<br>
<br>

#### Installation&Usage
---
##### Method 1(recommended):Composer Autoload,use composer's PSR-4 autoloader
**Installation**
1. copy the library files to some directory in the project's root directory,for example we use `/my_project/zego`,and the `/my_project/` directory is the root directory of the project.
2. `vim /my_project/composer.json` add `psr-4` autoload configuration
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
3. excute `composer dump-autoload` or `composer dump-autoload -o`(for production) or `composer update` commands, to generate autoload files.

**Usage**  
in `/my_project/xxx.php` file
```php
require 'vendor/autoload.php';
use ZEGO\ZegoServerAssistant;
use ZEGO\ZegoErrorCodes;

$appId = 1;
$roomId = 'demo';
$userId = 'demo';
$secret = 'fa94dd0f974cf2e293728a526b028271';
$token = ZegoServerAssistant::generateToken($appId,$roomId,$userId,["1"=> 1, "2"=>1],$secret,3600);
if( $token->code == ZegoErrorCodes::success ){
  print_r($token->token);
}
```

##### Method 2:Symfony Class Auto Loader,for the project with out using composer
**Installation**
1. copy the library files to some directory in the project's root directory,for example we use `/my_project/zego`,and the `/my_project/` directory is the root directory of the project.

**Usage**  
in `/my_project/xxx.php` file
```php
require_once 'zego/auto_loader.php';
use ZEGO\ZegoServerAssistant;
use ZEGO\ZegoErrorCodes;

$appId = 1;
$roomId = 'demo';
$userId = 'demo';
$secret = 'fa94dd0f974cf2e293728a526b028271';
$token = ZegoServerAssistant::generateToken($appId,$roomId,$userId,["1"=> 1, "2"=>1],$secret,3600);
if( $token->code == ZegoErrorCodes::success ){
  print_r($token->token);
}
```
