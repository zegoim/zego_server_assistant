# 简介

## 错误码说明

```javascript
enum ErrorCode
    {
        success                       = 0,  // 获取鉴权 token 成功
        appIDInvalid                  = 1,  // 调用方法时传入 appID 参数错误
        userIDInvalid                 = 3,  // 调用方法时传入 userID 参数错误
        secretInvalid                 = 5,  // 调用方法时传入 secret 参数错误
        effectiveTimeInSecondsInvalid = 6   // 调用方法时传入 effectiveTimeInSeconds 参数错误
    };
```

## GenerateToken04 参数及返回值说明

```javascript
// 参数
const appID: number;  // Zego派发的数字ID, 各个开发者的唯一标识
const userID: string;  //  用户 ID
const secret: string;   // 在获取 token 时进行 AES 加密的密钥
const effectiveTimeInSeconds: number;  // token 的有效时长，单位：秒

// 成功返回值
const token: string

//失败返回值
 interface ErrorInfo {
    errorCode: ErrorCode; // 错误码来自 ErrorCode
    errorMessage: string; // 对错误码的详细描述
 }
 const errorInfo:  ErrorInfo 
```

## demo

```javascript
const { generateToken04 } = require('../server/zegoServerAssistant');
// Rtc Examples
const appID = 123456789;
const secret = 'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx';
const userId = 'demo'; 
const effectiveTimeInSeconds = 3600; 

// Build token 
const token =  generateToken04(appID, userId, secret, effectiveTimeInSeconds);
 
```

## 源码引入方式使用说明

1. 前往 [Github 代码托管地址](https://github.com/zegoim/zego_server_assistant) 下载最新代码。
2. 将 nodejs/server 目录 拷贝到 项目中
3. 引入源码 `const { getToken } = require('../server/zegoServerAssistant');`
