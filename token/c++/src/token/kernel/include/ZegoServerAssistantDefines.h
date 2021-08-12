#ifndef __ZegoServerAssistantDefines__
#define __ZegoServerAssistantDefines__

#ifdef WIN32
#ifdef ZEGO_EXPORTS
#define ZEGOSA_API __declspec(dllexport)
#define ZEGOSACALL __cdecl
#else
#define ZEGOSA_API __declspec(dllimport)
#define ZEGOSACALL __cdecl
#endif
#else
#define ZEGOSA_API __attribute__((visibility("default")))
#define ZEGOSACALL
#endif

#include <string>

namespace ZEGO
{
namespace SERVER_ASSISTANT
{
    /**
     * @brief privilege 中 "key" 的值
     *
     */
    enum kPrivilege
    {
        kPrivilegeLogin = 1,   // privilege 中是否允许登录房间的 "key"; map
                               // 中对应的 "value" : 0 不允许, 1 允许
        kPrivilegePublish = 2  // privilege 中是否允许推流的 "key"; map 中对应的
                               // "value" : 0 不允许, 1 允许
    };

    /**
     * @brief ZegoServerAssistant 错误码
     *
     */
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

    /**
     * @brief 错误码及其描述
     *
     */
    struct ErrorInfo {
        ErrorCode   errorCode;     // 错误码来自 ErrorCode
        std::string errorMessage;  // 对错误码的详细描述
    };

    /**
     * @brief 在调用 GenerateToken 方法时得到的返回值
     * token: 计算得到的 token
     * errorInfo: 错误信息, errorInfo.errorCode 为 0 时计算 token 成功
     */
    struct ZegoTokenResult {
        std::string token;
        ErrorInfo   errorInfo;
    };
}  // namespace SERVER_ASSISTANT
}  // namespace ZEGO

#endif  //__ZegoServerAssistantDefines__