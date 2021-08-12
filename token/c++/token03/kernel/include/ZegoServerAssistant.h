#ifndef __ZegoServerAssistant__
#define __ZegoServerAssistant__

#include <stdint.h>
#include <map>
#include <string>

#include "ZegoServerAssistantDefines.h"

namespace ZEGO
{
namespace SERVER_ASSISTANT
{
    class ZEGOSA_API ZegoServerAssistant
    {
    public:
        /**
         * @brief 获取 token 的静态方法
         *
         * @param appID Zego派发的数字ID, 各个开发者的唯一标识
         * @param userID 用户ID
         * @param secret 在鉴权 token 计算过程中 AES 加密需要的密钥,32字节的字符串
         * @param effectiveTimeInSeconds token 的有效时长，单位：秒
         * @return ZegoTokenResult
         */
        static ZegoTokenResult GenerateToken(uint32_t appID, const std::string& userID, const std::string& secret, int64_t effectiveTimeInSeconds);
    };
}  // namespace SERVER_ASSISTANT

}  // namespace ZEGO

#endif  // __ZegoServerAssistant__
