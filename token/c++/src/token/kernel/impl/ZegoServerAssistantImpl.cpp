#include <stdint.h>
#include <time.h>
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock.h>
#elif __linux
#include <arpa/inet.h>
#endif

#include <common/ZegoCrypto.hpp>
#include "Base64.h"
#include "ZegoServerAssistantImpl.h"
#include "json_tools.hpp"

namespace ZEGO
{
namespace SERVER_ASSISTANT
{
    std::string ZegoServerAssistantImpl::GenerateToken(uint32_t appID, const std::string& roomID, const std::string& userID,
      const std::map<int, int>& privilege, const std::string& secret, int64_t effectiveTimeInSeconds)
    {
        time_t createTime;
        time(&createTime);
        time_t      expireTime = createTime + effectiveTimeInSeconds;
        uint64_t    nonce      = MakeNonce();
        TokenParams params(appID, roomID, userID, privilege, createTime, expireTime, nonce);

        std::string plainText = TokenToJson(params);

        std::string iv = MakeRandomIv();

        std::string encryptBuf = AesEncrypt(plainText, secret, iv);

        int64_t     bufferSize = encryptBuf.size() + 28;
        std::string buffer;
        buffer.resize(bufferSize);

        int64_t expire_time        = params.expireTime;
        int     expire_time_prefix = expire_time >> 32;
        int     expire_time_suffix = expire_time;
        expire_time_prefix         = htonl(expire_time_prefix);
        expire_time_suffix         = htonl(expire_time_suffix);

        ((int*) buffer.data())[0] = expire_time_prefix;
        ((int*) buffer.data())[1] = expire_time_suffix;

        int16_t ivSize       = iv.size();
        int8_t  ivSizePrefix = ivSize >> 8;
        int8_t  ivSizeSuffix = ivSize;

        ((int8_t*) buffer.data())[8] = ivSizePrefix;
        ((int8_t*) buffer.data())[9] = ivSizeSuffix;

        buffer.replace(10, 16, iv.c_str(), 16);

        int16_t encryptBufSize       = encryptBuf.size();
        int8_t  encryptBufSizePrefix = encryptBufSize >> 8;
        int8_t  encryptBufSizeSuffix = encryptBufSize;

        ((int8_t*) buffer.data())[26] = encryptBufSizePrefix;
        ((int8_t*) buffer.data())[27] = encryptBufSizeSuffix;

        buffer.replace(28, encryptBuf.size(), encryptBuf.c_str(), encryptBuf.size());

        int   outLen1   = base64_enc_len(buffer.size());
        char* outbuffer = new char[outLen1 + 1];
        int   outLen2   = base64_encode(outbuffer, (char*) buffer.c_str(), buffer.size());

        std::string result = "03" + std::string(outbuffer, outLen2);
        delete[] outbuffer;
        outbuffer = nullptr;
        return result;
    }

    int64_t ZegoServerAssistantImpl::MakeNonce()
    {
        srand(unsigned(time(0)));
        int64_t nonce = (int64_t) rand();
        return nonce;
    }

    std::string ZegoServerAssistantImpl::MakeRandomIv()
    {
        std::string str = "0123456789abcdefghijklmnopqrstuvwxyz";
        std::string buffer;
        srand(unsigned(time(0)));
        for (int i = 0; i < 16; ++i) {
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
        JSON_TOOLS::AddMember(document, "room_id", params.roomID.c_str(), allocator);
        JSON_TOOLS::AddMember(document, "user_id", params.userID.c_str(), allocator);
        rapidjson::Value privilege(rapidjson::kObjectType);
        for (auto member : params.privilege) {
            JSON_TOOLS::AddMember(privilege, std::to_string(member.first).c_str(), member.second, allocator);
        }
        JSON_TOOLS::AddMember(document, "privilege", &privilege, allocator);
        JSON_TOOLS::AddMember(document, "create_time", params.createTime, allocator);
        JSON_TOOLS::AddMember(document, "expire_time", params.expireTime, allocator);
        JSON_TOOLS::AddMember(document, "nonce", params.nonce, allocator);
        std::string result = JSON_TOOLS::JsonTools::rapiJsonToStr(document);
        return result;
    }

    std::string ZegoServerAssistantImpl::AesEncrypt(
      const std::string& origData, const std::string& key, const std::string& iv)
    {
        std::string inputOrigData(origData.c_str(), origData.size());
        std::string inputKey(key.c_str(), key.size());
        std::string inputIv(iv.c_str(), iv.size());

        ZEGO::AV::CZegoCrypto crypto;

        std::string encrypted = crypto.AESEnc(inputOrigData, inputKey, inputIv);
        return encrypted;
    }

}  // namespace SERVER_ASSISTANT
}  // namespace ZEGO
