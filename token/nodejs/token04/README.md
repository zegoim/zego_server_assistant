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
const payload: stirng; // token 业务扩展字段

// 成功返回值
const token: string

//失败返回值
 interface ErrorInfo {
    errorCode: ErrorCode; // 错误码来自 ErrorCode
    errorMessage: string; // 对错误码的详细描述
 }
 const errorInfo:  ErrorInfo 
```

## 普通 token 生成 demo

```javascript

const { generateToken04 } = require('../server/zegoServerAssistant');
// Rtc Examples
const appID = 123456789;
const secret = 'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx';
const userId = 'demo'; 
const effectiveTimeInSeconds = 3600; 
const payload = '';

// Build token 
const token =  generateToken04(appID, userId, secret, effectiveTimeInSeconds, payload);
 
```

## 强验证token 生成demo

* 强验证token用于对房间登录/推拉流权限需要进行强验证的场景，payload字段需要按照规格生成

```
const { generateToken04 } = require('../server/zegoServerAssistant');

const appID = 2375819786; // type: number
const secret = '3b9f207c003a70412e47b3cb2fcd204c';// type: 32 byte length string
const userId = 'demo';// type: string
const effectiveTimeInSeconds = 3600; //type: number; unit: s
const payloadObject = {
    room_id: 'demo',
    privilege: {
        1: 1,   // loginRoom: 1 pass , 0 not pass
        2: 0    // publishStream: 1 pass , 0 not pass
    },
    stream_id_list: null
}; 
const payload = JSON.stringify(payloadObject);
// Build token 
const token =  generateToken04(appID, userId, secret, effectiveTimeInSeconds, payload);

```

## 源码引入方式使用说明

1. 前往 [Github 代码托管地址](https://github.com/zegoim/zego_server_assistant) 下载最新代码。
2. 将 nodejs/token04/server 目录 拷贝到 项目中
3. 引入源码 `const { getToken } = require('../server/zegoServerAssistant');`
