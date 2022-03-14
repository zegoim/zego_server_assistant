# Introduction

# Instructions

## Import the header file, namespace

```c++
#include <stdint.h>
#include <map>
#include "ZegoServerAssistant.h"

using namespace ZEGO::SERVER_ASSISTANT;
```

## Error codes description

```c++
enum ErrorCode
    {
        success                       = 0,  // Token for authentication obtained successfully.
        appIDInvalid                  = 1,  // App ID parameter is invalid.
        userIDInvalid                 = 3,  // User ID parameter is invalid.
        secretInvalid                 = 5,  // Secret parameter is invalid.
        effectiveTimeInSecondsInvalid = 6   // effectiveTimeInSeconds parameter is invalid.
    };
```

## GenerateToken04 parameters description and return codes

```c++
// Parameters
uint32_t appID;  // App ID assigned by ZEGO, the unique identifier of user.
std::string userID;  //   User ID
std::string secret;   // The secret key for AES encryption when applying for token.
int64_t effectiveTimeInSeconds;  // The validity period of token, unit: second

// Return codes
ZegoToken04Result result;  // Struct contains two members:  token、 errorInfo; errorInfo includes errorCode, errorMessage
```

## general token generate demo 
- The general token is used for simple authorization of service interfaces, and the payload field can be empty.

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

## strict token generate demo
- The strict token is used in scenarios where strong authentication is required for login-room/push-stream/pull-stream permissions. The payload field should be generated according to the specifications.

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

# Instructions of integrating the SDK

## Dynamic library usage

### Compilers

- [cmake](https://cmake.org/)

CMake 3.6 or later.

### Compiling

1. Go to [Github- zego_server-assistant](https://github.com/zegoim/zego_server_assistant) to download the latest codes.
2. Go to the SDK to create the necessary build file.

```
cd <path/to/ZegoServerAssistant>
mkdir build
cd build
cmake ..
make
```

3. Add the link of the libzego_server_assistant.so generated in previous steps to your project, and add the header file ZegoServerAssistant.h to your project search path. And call the GenerateToken method as described above.

##  Import the codes 

1. Go to [Github - zego_server_assistant](https://github.com/zegoim/zego_server_assistant) to download the latest codes.
2. If rapidjson has been used in project, you can modify the header file path of rapidjson of ZegoServerAssistant project. you don’t need to import the common/rapidjson.
3. After importing the ZegoServerAssistant codes, ass the file directory to your project, and then call the GenerateToken method as described above. 
