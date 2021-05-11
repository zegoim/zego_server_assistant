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

$appId = 1;
$roomId = 'demo';
$userId = 'demo';
$secret = 'fa94dd0f974cf2e293728a526b028271';
$token = ZegoServerAssistant::getToken($appId,$roomId,$userId,["1"=> 1, "2"=>1],$secret);
print_r($token);
```

##### Method 2:Symfony Class Auto Loader,for the project with out using composer
**Installation**
1. copy the library files to some directory in the project's root directory,for example we use `/my_project/zego`,and the `/my_project/` directory is the root directory of the project.

**Usage**
in `/my_project/xxx.php` file
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