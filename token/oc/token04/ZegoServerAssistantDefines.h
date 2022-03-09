#ifndef __ZegoServerAssistantDefines__
#define __ZegoServerAssistantDefines__

#include <string>

namespace ZEGO
{
    namespace SERVER_ASSISTANT
    {
        enum ErrorCode
        {
            success = 0,  // 获取鉴权 token 成功
            appIDInvalid = 1,  // 调用方法时传入 appID 参数错误
            userIDInvalid = 3,  // 调用方法时传入 userID 参数错误
            secretInvalid = 5,  // 调用方法时传入 secret 参数错误
            effectiveTimeInSecondsInvalid = 6   // 调用方法时传入 effectiveTimeInSeconds 参数错误
        };
        struct ErrorInfo
        {
            ErrorCode   errorCode;     // 错误码来自 ErrorCode
            std::string errorMessage;  // 对错误码的详细描述
        };
        struct ZegoToken04Result
        {
            std::string token;
            ErrorInfo   errorInfo;
        };
    }
}

#endif  //__ZegoServerAssistantDefines__