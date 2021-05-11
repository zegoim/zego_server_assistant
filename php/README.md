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

$appId = 1;
$roomId = 'demo';
$userId = 'demo';
$secret = 'fa94dd0f974cf2e293728a526b028271';
$token = ZegoServerAssistant::getToken($appId,$roomId,$userId,["1"=> 1, "2"=>1],$secret);
print_r($token);
```

##### 方式二：Symfony Class Auto Loader 注册自动加载，适合在未使用composer的项目中使用此方式
**安装**
1. 拷贝文件包至项目根目录下的某个目录中，例如这里以`/my_project/zego`目录为例，其中`/my_project/`为项目根目录

**使用**
在`/my_project/xxx.php`文件中使用
```php
require_once 'zego/auto_loader.php';
use ZEGO\ZegoServerAssistant;

$appId = 1;
$roomId = 'demo';
$userId = 'demo';
$secret = 'fa94dd0f974cf2e293728a526b028271';
$token = ZegoServerAssistant::getToken($appId,$roomId,$userId,["1"=> 1, "2"=>1],$secret);
print_r($token);
```