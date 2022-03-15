# 简介

# 使用说明

## 需要引入的头文件、命名空间

```c++
#include <stdint.h>
#include <map>
#include "ZegoServerAssistant.h"

using namespace ZEGO::SERVER_ASSISTANT;
```

## 错误码说明

```c++
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

```c++
// 参数
uint32_t appID;  // Zego派发的数字ID, 各个开发者的唯一标识
std::string userID;  //  用户 ID
std::string secret;   // 在获取 token 时进行 AES 加密的密钥
int64_t effectiveTimeInSeconds;  // token 的有效时长，单位：秒

// 返回值
ZegoToken04Result result;  // 结构体有两个成员: token、 errorInfo, errorInfo 包含 errorCode, errorMessage
```

## 普通token 生成demo
- 普通token用于服务接口的简单权限验证的场景，payload字段可传空

```c++
void Sample()
{
    uint32_t appID = 1;
    std::string userID = "demo";
    std::string secret = "12345678900987654321123456789012";
    uint64_t effectiveTimeInSeconds = 3600;
    ZegoServerAssistant zegoServerAssistant;
    ZegoToken04Result result = zegoServerAssistant.GenerateToken04(appID, userID, secret, effectiveTimeInSeconds, "");
    printf("Sample:%s\n", result.token.c_str());
    printf("error code : %d\n", result.errorInfo.errorCode);
}
```

## 强验证token 生成demo
- 强验证token用于对房间登录/推拉流权限需要进行强验证的场景，payload字段需要按照规格生成

```c++

std::string GeneratePayload(const std::string& roomID, const std::map<int, int>& privilege, const std::vector<std::string>& streamIDList)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    ZEGO::JSON_TOOLS::AddMember(document, "room_id", roomID.c_str(), allocator);

    rapidjson::Value privilege_(rapidjson::kObjectType);
    for (auto member : privilege) 
    {
        ZEGO::JSON_TOOLS::AddMember(privilege_, std::to_string(member.first).c_str(), member.second, allocator);
    }
    ZEGO::JSON_TOOLS::AddMember(document, "privilege", &privilege_, allocator);

    rapidjson::Value streamIDList_(rapidjson::kArrayType);
    for (auto streamID : streamIDList)
    {
        rapidjson::Value streamID_(rapidjson::kStringType);
        streamID_.SetString(streamID.c_str(), allocator);
        streamIDList_.PushBack(streamID_, allocator);
    }
    document.AddMember("stream_id_list", streamIDList_, allocator);

    std::string result = ZEGO::JSON_TOOLS::JsonTools::rapiJsonToStr(document);
    return result;
}

void SampleForRTCRoom()
{
    uint32_t appID = 1;
    std::string roomID = "demo";
    std::string userID = "demo";
    std::string secret = "12345678900987654321123456789012";
    std::map<int, int> privilege {{kPrivilegeLogin, 1}, {kPrivilegePublish, 1}};
    uint64_t effectiveTimeInSeconds = 3600;
    std::vector<std::string> streamIDList {"sample", "sample2"};
    std::string payload = GeneratePayload(roomID, privilege, streamIDList);
    
    ZegoServerAssistant zegoServerAssistant;
    ZegoToken04Result result = zegoServerAssistant.GenerateToken04(appID, userID, secret, effectiveTimeInSeconds, payload);
    printf("Sample for rtc room:%s\n", result.token.c_str());
    printf("error code : %d\n", result.errorInfo.errorCode);
}

```

# 接入 SDK 说明

## 动态库方式使用说明

### 编译工具

- [cmake](https://cmake.org/)

安装 cmake 3.6 或以上版本。

### 编译执行

1. 前往 [Github 代码托管地址]() 下载最新代码。
2. 进入 SDK 创建生成必要的构建文件。

```
cd <path/to/ZegoServerAssistant>
mkdir build
cd build
cmake ..
make
```

3. 将上述步骤生成的动态库文件 libzego_server_assistant.so 链接到项目中，将 头文件 ZegoServerAssistant.h 添加到项目搜索路径中，按照上文使用说明使用 GenerateToken04 方法。

## 源码引入方式使用说明

1. 前往 [Github 代码托管地址](https://github.com/zegoim/zego_server_assistant) 下载最新代码。
2. 若项目中已使用了 rapidjson，可以修改 ZegoServerAssistant 项目中 rapidjson 的头文件引入路径，并无需引入 common/rapidjson。
3. 引入 ZegoServerAssistant 源码后，需要将文件加入项目的搜索路径，按照上文使用说明使用 GenerateToken04 方法。
