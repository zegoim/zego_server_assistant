[toc]
# 1. Installation
## Method 1(recommend): from official repository of composer

```bash
$ composer require zegoim/server_assistant:0.0.1
```

## Method 2(recommend): by path type of composer repositories
The project's files structure：
```
.
├── composer.json
├── composer.lock
├── packages
│   └── zego_server_assistant
└── src
```

Add a repository of path type in repositories field in `composer.json`
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

Run 
```bash
$ composer require zegoim/server_assistant:0.0.1
```

## Method 3 : Composer Autoload, use composer's PSR-4 autoloader

1. Copy the library files into a directory in the root of your project, For example we copied files into `/my_project/zego`, And the directory `/my_project/` is the root directory of the project.
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
3. Run `composer dump-autoload` or `composer dump-autoload -o`(for production) or `composer update` to generate autoload files.


## Method 4: Symfony Class Auto Loader, for the projects that is not using composer

1. Copy the library files into a directory in the root of your project, For example we copied files into `/my_project/zego`, And the directory `/my_project/` is the root directory of the project.

require auto loader before using the library
```php
require_once 'zego/auto_loader.php';
```

# 2. Usage  
## general token generate demo
- in `/my_project/xxx.php` file
- The general token is used for simple authorization of service interfaces, and the payload field can be empty.
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


## strict token generate demo
- in `/my_project/xxx.php` file
- The strict token is used in scenarios where strong authentication is required for login-room/push-stream/pull-stream permissions. The payload field should be generated according to the specifications.

```php
require 'vendor/autoload.php';
use ZEGO\ZegoServerAssistant;
use ZEGO\ZegoErrorCodes;

const PrivilegeKeyLogin   = 1; 
const PrivilegeKeyPublish = 2; 

const PrivilegeEnable     = 1; 
const PrivilegeDisable    = 0; 

$appId = 1;
$userId = 'demo';
$roomId = "demo";
$secret = 'fa94dd0f974cf2e293728a526b028271';
$rtcRoomPayLoad = [
    'room_id' => $roomId, 
    'privilege' => [    
        PrivilegeKeyLogin => PrivilegeEnable,
        PrivilegeKeyPublish => PrivilegeDisable,
    ],
    'stream_id_list' => [] 
];

$payload = json_encode($rtcRoomPayLoad);

$token = ZegoServerAssistant::generateToken04($appId, $userId, $secret, 3600, $payload);
if( $token->code == ZegoErrorCodes::success ){
 print_r($token);
}
```

# 3. Error codes

```php
namespace ZEGO;

class ZegoErrorCodes{
    const success                       = 0;  // Token for authentication obtained successfully.
    const appIDInvalid                  = 1;  // App ID parameter is invalid.
    const userIDInvalid                 = 3;  // User ID parameter is invalid.
    const secretInvalid                 = 5;  // Secret parameter is invalid.
    const effectiveTimeInSecondsInvalid = 6;  // effectiveTimeInSeconds parameter is invalid.
}
```


# 4. generateToken04 parameters description and return codes

```php
    /**
     * Use the following parameters to generate the token for authentication when accessing to ZEGO service
     *
     * @param integer $appId App ID assigned by ZEGO, the unique identifier of user.
     * @param string $userId User ID
     * @param string $secret The secret key corresponding to AppID assigned by ZEGO. Please keep it carefully.
     * @param integer $effectiveTimeInSeconds The validity period of token, unit: second
     * @param string $payload Business extension field, JSON string
     * @return ZegoAssistantToken  Returned token content, the value is the ZEGO\ZegoAssistantToken object. Before using the token, check whether the code property of the object is  ZEGO\ZegoErrorCodes::success. The actual token content is stored in the token property.
     */
    public static function generateToken04(int $appId, string $userId, string $secret, int $effectiveTimeInSeconds, string $payload)


```

Returned value is `ZEGO\ZegoAssistantToken` object：
```php

namespace ZEGO;

class ZegoAssistantToken{
    public $code;
    public $message = '';
    public $token;
}
```
