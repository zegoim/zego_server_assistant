#ifndef __ZegoServerAssistantImpl__
#define __ZegoServerAssistantImpl__

#include <stdint.h>
#include <map>
#include <string>
#include "ZegoServerAssistantDefines.h"

struct TokenParams {
    uint32_t           appID;
    std::string        userID;
    int32_t            nonce;
    int64_t            createTime;
    int64_t            expireTime;
    std::string        payload;
    TokenParams(uint32_t appID1, const std::string& userID1, int64_t createTime1, int64_t expireTime1, int32_t nonce1, const std::string& payload1)
      : appID(appID1), userID(userID1), createTime(createTime1), expireTime(expireTime1), nonce(nonce1), payload(payload1)
    {}
};

namespace ZEGO
{
namespace SERVER_ASSISTANT
{
    class ZegoServerAssistantImpl
    {
    public:
        std::string GenerateToken04(uint32_t appID, const std::string& userID, const std::string& secret, int64_t effectiveTimeInSeconds, const std::string& payload);

    private:
        int32_t MakeIntNonce();

        // 随机生成字节字符串，用作 AES 加密，放在密文前一起做 Base64 编码
        // 编码最终生成 token
        std::string MakeStrNonce(int length);

        // 把 token 信息转成 json
        std::string TokenToJson(const TokenParams& params);

        // 进行 AES 加密
        std::string AesGCMEncrypt(const std::string& origData, const std::string& key, const std::string& nonce);
    };
}  // namespace SERVER_ASSISTANT

}  // namespace ZEGO

#endif  // __ZegoServerAssistantImpl__
