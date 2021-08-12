#ifndef ZegoCrypto_hpp
#define ZegoCrypto_hpp

#include <stdint.h>
#include <string>

namespace ZEGO
{
	namespace AV
	{
        #define BLOCK_SIZE (16)
        
		class CZegoCrypto
		{
		public:
			using BYTE = unsigned char;
			
			std::string AESDec(std::string& encyptedText, const std::string& key, const std::string& iv = "");
			std::string AESEnc(const std::string& plainText, const std::string& key, const std::string& iv = "");
            
			std::string AESEncECB(const std::string& plainText, const std::string& key);
			std::string AESDecECB(std::string& encyptedText, const std::string& key);

		private:
			void InitKV(const std::string& key, const std::string& iv);
			std::string PKCS7Padding(const std::string& plainText);

		private:
			BYTE m_Key[32];     // max
			BYTE m_IV[BLOCK_SIZE];
		};
	}
}

#endif /* ZegoCrypto_hpp */
