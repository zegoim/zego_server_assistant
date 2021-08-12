#include "ZegoServerAssistant.h"
#include "ZegoServerAssistantDefines.h"
#include "ZegoServerAssistantImpl.h"

namespace ZEGO
{
namespace SERVER_ASSISTANT
{
    ZegoToken04Result ZegoServerAssistant::GenerateToken04(uint32_t appID, const std::string& userID, const std::string& secret, int64_t effectiveTimeInSeconds)
    {
        ZegoToken04Result tokenResult;
        if (appID == 0) {
            tokenResult.token                  = "";
            tokenResult.errorInfo.errorCode    = appIDInvalid;
            tokenResult.errorInfo.errorMessage = "appID invalid";
            return tokenResult;
        }
        if (userID == "") {
            tokenResult.token                  = "";
            tokenResult.errorInfo.errorCode    = userIDInvalid;
            tokenResult.errorInfo.errorMessage = "userID invalid";
            return tokenResult;
        }
        if (secret.size() != 32) {
            tokenResult.token                  = "";
            tokenResult.errorInfo.errorCode    = secretInvalid;
            tokenResult.errorInfo.errorMessage = "secret must be a 32 byte string";
            return tokenResult;
        }
        if (effectiveTimeInSeconds <= 0) {
            tokenResult.token                  = "";
            tokenResult.errorInfo.errorCode    = effectiveTimeInSecondsInvalid;
            tokenResult.errorInfo.errorMessage = "effectiveTimeInSeconds invalid";
            return tokenResult;
        }
        ZegoServerAssistantImpl serverAssistantImpl;
        std::string             result
          = serverAssistantImpl.GenerateToken(appID, userID, secret, effectiveTimeInSeconds);
        tokenResult.token                  = result;
        tokenResult.errorInfo.errorCode    = success;
        tokenResult.errorInfo.errorMessage = "success";
        return tokenResult;
    }
}  // namespace SERVER_ASSISTANT

}  // namespace ZEGO
