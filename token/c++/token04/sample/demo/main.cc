#include <stdint.h>
#include <map>
#include <string>
#include <vector>
#include "ZegoServerAssistantDefines.h"
#include "ZegoServerAssistant.h"
#include "json_tools.hpp"

using namespace ZEGO::SERVER_ASSISTANT;

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
//
//基础鉴权token生成示例代码
//
void Sample()
{
    uint32_t appID = 1;
    std::string userID = "demo";
    std::string secret = "12345678900987654321123456789012";
    uint64_t effectiveTimeInSeconds = 3600; // token 过期时间，单位：秒
    ZegoServerAssistant zegoServerAssistant;
    ZegoToken04Result result = zegoServerAssistant.GenerateToken04(appID, userID, secret, effectiveTimeInSeconds, "");
    printf("Sample:%s\n", result.token.c_str());
    printf("error code : %d\n", result.errorInfo.errorCode);
}

//
//权限认证token生成示例代码，使用前需联系即构技术支持开通功能
//
void SampleForRTCRoom()
{
    uint32_t appID = 1;
    std::string roomID = "demo";
    std::string userID = "demo";
    std::string secret = "12345678900987654321123456789012";
    // 此处代表允许登录，允许推流；如果 value 从 1 改为 0，则为不允许
    std::map<int, int> privilege {{kPrivilegeLogin, 1}, {kPrivilegePublish, 1}};
    uint64_t effectiveTimeInSeconds = 3600; // token 过期时间，单位：秒
    std::vector<std::string> streamIDList {"sample", "sample2"};
    std::string payload = GeneratePayload(roomID, privilege, streamIDList);
    
    ZegoServerAssistant zegoServerAssistant;
    ZegoToken04Result result = zegoServerAssistant.GenerateToken04(appID, userID, secret, effectiveTimeInSeconds, payload);
    printf("Sample for rtc room:%s\n", result.token.c_str());
    printf("error code : %d\n", result.errorInfo.errorCode);
}

int main() 
{
    Sample();
    SampleForRTCRoom();
    return 0;
}