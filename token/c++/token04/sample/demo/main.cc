#include <stdint.h>
#include <map>
#include "ZegoServerAssistant.h"

using namespace ZEGO::SERVER_ASSISTANT;

int main() 
{
    uint32_t appID = 1;
    std::string userID = "demo";
    std::string secret = "12345678900987654321123456789012";
    uint64_t effectiveTimeInSeconds = 3600;
    ZegoServerAssistant zegoServerAssistant;
    ZegoToken04Result result = zegoServerAssistant.GenerateToken04(appID, userID, secret, effectiveTimeInSeconds);
    printf("%s\n", result.token.c_str());
    printf("error code : %d\n", result.errorInfo.errorCode);
    return 0;
}