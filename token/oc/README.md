# 简介

# 使用说明

## 需要引入的头文件

```oc
#include "token04/ZegoToken.h"
#include "token04/json_tools.hpp"

```

## 错误码说明

```oc
typedef NS_ENUM(NSUInteger, ZegoErrorCode) {
    success = 0,  // 获取鉴权 token 成功
    appIDInvalid = 1,  // 调用方法时传入 appID 参数错误
    userIDInvalid = 3,  // 调用方法时传入 userID 参数错误
    secretInvalid = 5,  // 调用方法时传入 secret 参数错误
    effectiveTimeInSecondsInvalid = 6   // 调用方法时传入 effectiveTimeInSeconds 参数错误
};
```

## GenerateToken04 参数及返回值说明

```c++
// 参数
long long appID;  // Zego派发的数字ID, 各个开发者的唯一标识
NSString* userID;  //  用户 ID
NSString* secret;   // 在获取 token 时进行 AES 加密的密钥
long long effectiveTimeInSeconds;  // token 的有效时长，单位：秒

// 返回值
ZegoToken04Result result;  // 有两个成员: token、 errorInfo, errorInfo 包含 errorCode, errorMessage
```

## 普通token 生成demo
- 普通token用于服务接口的简单权限验证的场景，payload字段可传空

```c++
- (void) OnMakeToken
    NSString * serverKey= @"your_server_key";
    NSString * userID= @"demo_id_name";
    long long appid= 1;
    long long expireTime = 36000;
    
    ZegoToken04Result* tokenResult = [ZegoToken GenerateToken04:appid userID:userID secret:serverKey effectiveTimeInSeconds:expireTime payload:nil];
    
    if(tokenResult.errorInfo.errorCode == 0)
    {
        //success
        return;
    }
    else
    {
        //fail
    }
    
    return;  
}
```

## 强验证token 生成demo
- 强验证token用于对房间登录/推拉流权限需要进行强验证的场景，payload字段需要按照规格生成

```c++

- (void) OnMakeToken
{
    NSString * serverKey= @"your_server_key;
    NSString * userID= @"demo_id_name";
    long long appid= 1;
    long long expireTime = 36000;
    
	//playload 为更高级别的权限控制，有需要可以咨询技术支持，后台配置开通后，可使用此方法生成Token
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("room_id","",allocator);  //填入房间id,不为空，则指定房间可以登录
    
	int loginRoomRole = 1;
	int publishRole = 1;
    rapidjson::Value privilege(rapidjson::kObjectType);
    privilege.AddMember("1",loginRoomRole,allocator);  // 生成的Token 包含登录房间权限
    privilege.AddMember("2",publishRole,allocator);  // 生成的Token 包含推流权限
    document.AddMember("privilege",privilege,allocator);
    
    rapidjson::Value streamList(rapidjson::kArrayType);
    document.AddMember("stream_id_list",streamList,allocator); //填入推流id,不为空，则只能推指定流
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    std::string payloadJson = buffer.GetString();
    
    NSString* payload = [NSString stringWithUTF8String:payloadJson.c_str()];
    
    ZegoToken04Result* tokenResult = [ZegoToken GenerateToken04:appid userID:userID secret:serverKey effectiveTimeInSeconds:expireTime payload:payload];
    
    if(tokenResult.errorInfo.errorCode == 0)
    {
         //success
        return;
    }
    else
    {
         //fail
    }
    return;
    
}
```

# 接入 SDK 说明
- 复制 \oc\rapidjson \oc\token04 加入到你的工程项目，调用GenerateToken04接口.
