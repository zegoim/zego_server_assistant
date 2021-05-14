#include "ZegoServerAssistant.h"
#include "ZegoServerAssistantDefines.h"
#include "ZegoServerAssistantImpl.h"

namespace ZEGO
{
namespace SERVER_ASSISTANT
{
    ZegoTokenResult ZegoServerAssistant::GenerateToken(uint32_t appID, const std::string& roomID, const std::string& userID,
      const std::map<int, int>& privilege, const std::string& secret, int64_t effectiveTimeInSeconds)
    {
        ZegoTokenResult tokenResult;
        if (appID == 0) {
            tokenResult.token                  = "";
            tokenResult.errorInfo.errorCode    = appIDInvalid;
            tokenResult.errorInfo.errorMessage = "appID invalid";
            return tokenResult;
        }
        if (roomID == "") {
            tokenResult.token                  = "";
            tokenResult.errorInfo.errorCode    = roomIDInvalid;
            tokenResult.errorInfo.errorMessage = "roomID invalid";
            return tokenResult;
        }
        if (userID == "") {
            tokenResult.token                  = "";
            tokenResult.errorInfo.errorCode    = userIDInvalid;
            tokenResult.errorInfo.errorMessage = "userID invalid";
            return tokenResult;
        }
        if (privilege.size() != 2 || privilege.count(kPrivilegeLogin) != 1 || privilege.count(kPrivilegePublish) != 1
            || (privilege.begin()->second != 0 && privilege.begin()->second != 1)
            || ((++privilege.begin())->second != 0 && (++privilege.begin())->second != 1)) {
            tokenResult.token                  = "";
            tokenResult.errorInfo.errorCode    = privilegeInvalid;
            tokenResult.errorInfo.errorMessage = "privilege key must include 1 and 2; the value must be number";
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
          = serverAssistantImpl.GenerateToken(appID, roomID, userID, privilege, secret, effectiveTimeInSeconds);
        tokenResult.token                  = result;
        tokenResult.errorInfo.errorCode    = success;
        tokenResult.errorInfo.errorMessage = "success";
        return tokenResult;
    }
}  // namespace SERVER_ASSISTANT

}  // namespace ZEGO