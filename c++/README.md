# 简介

# 使用说明

## 需要引入的头文件、命名空间

```c++
#include <stdint.h>
#include <map>
#include "ZegoServerAssistant.h"

using namespace ZEGO::SERVER_ASSISTANT;
```

## 房间权限说明

```c++
enum ZEGOSA_API kPrivilege
{
    kPrivilegeLogin = 1,  // privilege 中是否允许登录房间的 "key"; map 中对应的
                          // "value" : 0 不允许, 1 允许
    kPrivilegePublish = 2  // privilege 中是否允许推流的 "key"; map 中对应的
                           // "value" : 0 不允许, 1 允许
};
```

## 错误码说明

```c++
enum ErrorCode
    {
        success                       = 0,  // 获取鉴权 token 成功
        appIDInvalid                  = 1,  // 调用方法时传入 appID 参数错误
        roomIDInvalid                 = 2,  // 调用方法时传入 roomID 参数错误
        userIDInvalid                 = 3,  // 调用方法时传入 userID 参数错误
        privilegeInvalid              = 4,  // 调用方法时传入 privilege 参数错误
        secretInvalid                 = 5,  // 调用方法时传入 secret 参数错误
        effectiveTimeInSecondsInvalid = 6   // 调用方法时传入 effectiveTimeInSeconds 参数错误
    };
```

## GenerateToken参数及返回值说明

```c++
// 参数
uint32_t appID;  // Zego派发的数字ID, 各个开发者的唯一标识
std::string roomID;  // 房间 ID
std::string userID;  //  用户 ID
std::map<int, int> privilege;  // 房间权限
std::string secret;   // 在获取 token 时进行 AES 加密的密钥
std::string effectiveTimeInSeconds;  // token 的有效时长，单位：秒

// 返回值
ZegoTokenResult result;  // 结构体有两个成员: token、 errorInfo, errorInfo 包含 errorCode, errorMessage
```

## demo

```c++
int main() 
{
    uint32_t appID = 1;
    std::string roomID = "demo";
    std::string userID = "demo";
    std::map<int, int> privilege;
    privilege.insert(std::make_pair(kPrivilegeLogin, 1));
    privilege.insert(std::make_pair(kPrivilegePublish, 1));
    std::string secret = "fa94dd0f974cf2e293728a526b028271";
    uint64_t effectiveTimeInSeconds = 3600;
    ZegoTokenResult result = ZegoServerAssistant::GenerateToken(appID, roomID,
      userID, privilege,
      secret, effectiveTimeInSeconds);
    printf("%s\n", result.token.c_str());
    printf("error code : %d", result.errorCode);
    return 0;
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

3. 将上述步骤生成的动态库文件 libzego_server_assistant.so 链接到项目中，将 头文件 ZegoServerAssistant.h 添加到项目搜索路径中，按照上文使用说明使用 GenerateToken方法。

## 源码引入方式使用说明

1. 前往 [Github 代码托管地址]() 下载最新代码。
2. 若项目中已使用了 rapidjson，可以修改 ZegoServerAssistant 项目中 rapidjson 的头文件引入路径，并无需引入 common/rapidjson。
3. 引入 ZegoServerAssistant 源码后，需要将文件加入项目的搜索路径，按照上文使用说明使用 GenerateToken 方法。
