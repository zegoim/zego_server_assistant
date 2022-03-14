# Introduction

# Instructions

## Import the header file

```oc
#include "token04/ZegoToken.h"
#include "token04/json_tools.hpp"

```

##  Error codes description

```oc
typedef NS_ENUM(NSUInteger, ZegoErrorCode) {
    success = 0,  // Token for authentication obtained successfully.
    appIDInvalid = 1,  // App ID parameter is invalid.
    userIDInvalid = 3,  // User ID parameter is invalid.
    secretInvalid = 5,  // Secret parameter is invalid.
    effectiveTimeInSecondsInvalid = 6   // effectiveTimeInSeconds parameter is invalid.
};
```

## GenerateToken04 参数及返回值说明

```c++
// 参数
long long appID;  //App ID assigned by ZEGO, the unique identifier of user.
NSString* userID;  //   User ID
NSString* secret;   // The secret key for AES encryption when applying for token.
long long effectiveTimeInSeconds;  // The validity period of token, unit: second

// 返回值
ZegoToken04Result result;  //  Struct contains two members:  token、 errorInfo; errorInfo includes errorCode, errorMessage
```

## 普通token 生成demo
- The general token is used for simple authorization of service interfaces, and the payload field can be empty.

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
- The strict token is used in scenarios where strong authentication is required for login-room/push-stream/pull-stream permissions. The payload field should be generated according to the specifications.

```c++

- (void) OnMakeToken
{
    NSString * serverKey= @"your_server_key;
    NSString * userID= @"demo_id_name";
    long long appid= 1;
    long long expireTime = 36000;
    
	//playload
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("room_id","",allocator);  
    
	int loginRoomRole = 1;
	int publishRole = 1;
    rapidjson::Value privilege(rapidjson::kObjectType);
    privilege.AddMember("1",loginRoomRole,allocator); 
    privilege.AddMember("2",publishRole,allocator); 
    document.AddMember("privilege",privilege,allocator);
    
    rapidjson::Value streamList(rapidjson::kArrayType);
    document.AddMember("stream_id_list",streamList,allocator); 
    
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

# Instructions of integrating the SDK
- copy file \oc\rapidjson \oc\token04 to your project，call GenerateToken04 function.
