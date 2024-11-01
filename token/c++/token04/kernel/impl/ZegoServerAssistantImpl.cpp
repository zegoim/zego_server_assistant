#include <stdint.h>
#include <time.h>
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock.h>
#elif __linux
#include <arpa/inet.h>
#endif

#include "../modules/common/aes_gcm/gcm.h"
#include "Base64.h"
#include "ZegoServerAssistantImpl.h"
#include "json_tools.hpp"

namespace ZEGO
{
namespace SERVER_ASSISTANT
{
    std::string ZegoServerAssistantImpl::GenerateToken04(uint32_t appID, const std::string& userID, const std::string& secret, int64_t effectiveTimeInSeconds, const std::string& payload)
    {
        time_t createTime;
        time(&createTime);
        time_t      expireTime = createTime + effectiveTimeInSeconds;
        int32_t    nonce      = MakeIntNonce();
        TokenParams params(appID, userID, createTime, expireTime, nonce, payload);

        std::string plainText = TokenToJson(params);

        std::string strNonce = MakeStrNonce(12);

        std::string encryptBuf = AesGCMEncrypt(plainText, secret, strNonce);

        int64_t     bufferSize = encryptBuf.size() + strNonce.size() + 13;
        int start = 0;

        std::string buffer;
        buffer.resize(bufferSize);

        int64_t expire_time        = params.expireTime;
        int     expire_time_prefix = expire_time >> 32;
        int     expire_time_suffix = expire_time;
        expire_time_prefix         = htonl(expire_time_prefix);
        expire_time_suffix         = htonl(expire_time_suffix);

        ((int*) buffer.data())[0] = expire_time_prefix;
        ((int*) buffer.data())[1] = expire_time_suffix;

        start += sizeof(int64_t);

        int16_t ivSize       = strNonce.size();
        int8_t  ivSizePrefix = ivSize >> 8;
        int8_t  ivSizeSuffix = ivSize;

        ((int8_t*) buffer.data())[start++] = ivSizePrefix;
        ((int8_t*) buffer.data())[start++] = ivSizeSuffix;

        buffer.replace(start, strNonce.size(), strNonce.c_str(), strNonce.size());
        start += strNonce.size();

        int16_t encryptBufSize       = encryptBuf.size();
        int8_t  encryptBufSizePrefix = encryptBufSize >> 8;
        int8_t  encryptBufSizeSuffix = encryptBufSize;

        ((int8_t*) buffer.data())[start++] = encryptBufSizePrefix;
        ((int8_t*) buffer.data())[start++] = encryptBufSizeSuffix;

        buffer.replace(start, encryptBuf.size(), encryptBuf.c_str(), encryptBuf.size());
        start += encryptBuf.size();

        ((int8_t*)buffer.data())[start] = AesEncryptModeGCM;

        int   outLen1   = base64_enc_len(buffer.size());
        char* outbuffer = new char[outLen1 + 1];
        int   outLen2   = base64_encode(outbuffer, (char*) buffer.c_str(), buffer.size());

        std::string result = "04" + std::string(outbuffer, outLen2);
        delete[] outbuffer;
        outbuffer = nullptr;
        return result;
    }

    int32_t ZegoServerAssistantImpl::MakeIntNonce()
    {
        srand(unsigned(time(0)));
        int32_t nonce = (int32_t) rand();
        return nonce;
    }

    std::string ZegoServerAssistantImpl::MakeStrNonce(int length)
    {
        std::string str = "0123456789abcdefghijklmnopqrstuvwxyz";
        std::string buffer;
        srand(unsigned(time(0)));
        for (int i = 0; i < length; ++i) {
            buffer += str[(rand() % (str.length()))];
        }
        return buffer;
    }

    std::string ZegoServerAssistantImpl::TokenToJson(const TokenParams& params)
    {
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        JSON_TOOLS::AddMember(document, "app_id", params.appID, allocator);
        JSON_TOOLS::AddMember(document, "user_id", params.userID.c_str(), allocator);
        JSON_TOOLS::AddMember(document, "nonce", params.nonce, allocator);
        JSON_TOOLS::AddMember(document, "ctime", params.createTime, allocator);
        JSON_TOOLS::AddMember(document, "expire", params.expireTime, allocator);
        JSON_TOOLS::AddMember(document, "payload", params.payload.c_str(), allocator);
        std::string result = JSON_TOOLS::JsonTools::rapiJsonToStr(document);

        return result;
    }

    std::string ZegoServerAssistantImpl::AesGCMEncrypt(
      const std::string& origData, const std::string& key, const std::string& nonce)
    {
        std::string result;
        result.resize(origData.size() + 16);

        aes_init_keygen_tables();

        gcm_context ctx;            // includes the AES context structure

        gcm_setkey(&ctx, (const uchar*)key.c_str(), (const uint)key.size());

        gcm_crypt_and_tag(&ctx, ENCRYPT, (const uchar*)nonce.c_str(), nonce.size(), NULL, 0,
            (const uchar*)origData.c_str(), (uchar*)result.c_str(), origData.size(), (uchar*)result.c_str() + origData.size(), 16);

        gcm_zero_ctx(&ctx);
        return result;
    }

}  // namespace SERVER_ASSISTANT
}  // namespace ZEGO
