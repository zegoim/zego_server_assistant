#include <assert.h>
#include <cstring>

#include "ZegoCrypto.hpp"
#include "crypto-algorithms/aes.h"


namespace ZEGO
{
	namespace AV
	{
		void CZegoCrypto::InitKV(const std::string& key, const std::string& iv) 
		{
			if (iv.length() != BLOCK_SIZE)
			{
				memset(m_IV, 0, BLOCK_SIZE);
			}
			else 
			{
				memcpy(m_IV, iv.c_str(), BLOCK_SIZE);
			}

			uint32_t keyLength = key.length();
			assert(keyLength == 16 || keyLength == 32);
			memcpy(m_Key, key.c_str(), keyLength);
		}

		std::string CZegoCrypto::PKCS7Padding(const std::string& plainText)
		{
			uint32_t fitSize = plainText.size();
			if (fitSize % BLOCK_SIZE != 0)
			{
				fitSize = (fitSize / BLOCK_SIZE + 1) * BLOCK_SIZE;
			}

			std::string padded;
			padded.resize(fitSize);
			
			memset((char*)padded.c_str(), fitSize-plainText.size(), sizeof(BYTE) * fitSize);
			memcpy((char*)padded.c_str(), plainText.c_str(), plainText.size());

			return padded;
		}


		void zego_aes_encrypt_cbc(char* plainText, uint32_t len, char* encrypted, BYTE key[], uint32_t keyLength, BYTE iv[])
		{
			AES_WORD key_schedule[60] = { 0 };
			aes_key_setup(key, key_schedule, keyLength * 8);
			aes_encrypt_cbc((BYTE*)plainText, len, (BYTE*)encrypted, key_schedule, keyLength * 8, iv);
		}


		void zego_aes_decrypt_cbc(char* encrypted, uint32_t len, char* plainText, BYTE key[], uint32_t keyLength, BYTE iv[])
		{
			AES_WORD key_schedule[60] = { 0 };
			aes_key_setup(key, key_schedule, keyLength * 8);
			aes_decrypt_cbc((BYTE*)encrypted, len, (BYTE*)plainText, key_schedule, keyLength * 8, iv);
		}


		void zego_aes_encrypt_ecb(char* plainText, uint32_t len, char* encrypted, BYTE key[], uint32_t keyLength)
		{
			AES_WORD key_schedule[60] = { 0 };
			aes_key_setup(key, key_schedule, keyLength * 8);

			for (unsigned int i = 0; i < len / AES_BLOCK_SIZE; i++) 
			{
				aes_encrypt((BYTE*)(plainText + i * AES_BLOCK_SIZE), (BYTE*)(encrypted + i * AES_BLOCK_SIZE), key_schedule, keyLength * 8);
			}
		}


		void zego_aes_decrypt_ecb(char* encrypted, uint32_t len, char* plainText, BYTE key[], uint32_t keyLength)
		{
			AES_WORD key_schedule[60] = { 0 };
			aes_key_setup(key, key_schedule, keyLength * 8);

			for (unsigned int i = 0; i < len / AES_BLOCK_SIZE; i++)
			{
				aes_decrypt((BYTE*)(encrypted + i * AES_BLOCK_SIZE), (BYTE*)(plainText + i * AES_BLOCK_SIZE), key_schedule, keyLength * 8);
			}
		}


		std::string CZegoCrypto::AESEnc(const std::string& plainText, const std::string& key, const std::string& iv) 
		{

			InitKV(key, iv);

			auto padded = PKCS7Padding(plainText);
			std::string encrypted;
			encrypted.resize(padded.size());

			zego_aes_encrypt_cbc((char*)padded.c_str(), padded.size(), (char*)encrypted.c_str(), m_Key, key.size(), m_IV);
			return encrypted;
		}
        
		std::string CZegoCrypto::AESDec(std::string& encyptedText, const std::string& key, const std::string& iv)
		{
			InitKV(key, iv);

			assert(encyptedText.length() % 16 == 0);

			std::string decrypted;
			decrypted.resize(encyptedText.size());
			zego_aes_decrypt_cbc((char*)encyptedText.c_str(), encyptedText.size(), (char*)decrypted.c_str(), m_Key, key.size(), m_IV);
			return decrypted;
		}

		std::string CZegoCrypto::AESEncECB(const std::string& plainText, const std::string& key)
		{
			InitKV(key, "");

			auto padded = PKCS7Padding(plainText);
			std::string encrypted;
			encrypted.resize(padded.size());

			zego_aes_encrypt_ecb((char*)padded.c_str(), padded.size(), (char*)encrypted.c_str(), m_Key, key.size());
			return encrypted;
		}


		std::string CZegoCrypto::AESDecECB(std::string& encyptedText, const std::string& key)
		{
			InitKV(key, "");

			std::string decrypted;
			decrypted.resize(encyptedText.size());

			zego_aes_decrypt_ecb((char*)encyptedText.c_str(), encyptedText.size(), (char*)decrypted.c_str(), m_Key, key.size());

			return decrypted;
		}
 
        
	}
}