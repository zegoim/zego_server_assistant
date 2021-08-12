#include <stdint.h>
#include <map>
#include "ZegoServerAssistant.h"

using namespace ZEGO::SERVER_ASSISTANT;

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
    ZegoServerAssistant zegoServerAssistant;
    ZegoTokenResult result = zegoServerAssistant.GenerateToken(appID, roomID,
      userID, privilege,
      secret, effectiveTimeInSeconds);
    printf("%s\n", result.token.c_str());
    printf("error code : %d\n", result.errorInfo.errorCode);
    return 0;
}