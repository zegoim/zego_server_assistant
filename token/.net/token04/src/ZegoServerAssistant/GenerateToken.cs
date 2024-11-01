using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace ZegoServerAssistant
{

    public enum ErrorCode
    {
        success = 0,  // "success"
        appIDInvalid = 1,  // "appID invalid"
        userIDInvalid = 3,  // "userID invalid"
        secretInvalid = 5,  // "secret must be a 32 byte string"
        effectiveTimeInSecondsInvalid = 6  // "effectiveTimeInSeconds invalid"
    };

    public enum AesEncryptMode
    {
        AesEncryptModeCBCPKCS5Padding = 0, // AES加密模式: AES/CBC/PKCS5Padding； 废弃
        AesEncryptModeGCM = 1 // AES加密模式: AES/GCM；推荐使用
    }

    public class ErrorInfo
    {
        public ErrorCode errorCode;
        public string errorMessage;
    }

    public class GenerateTokenResult
    {
        public string token;
        public ErrorInfo errorInfo;
    }

    public static class ServerAssistant
    {
        public static GenerateTokenResult GenerateToken04(uint appID, string userID, string secret, long effectiveTimeInSeconds, string payload)
        {
            GenerateTokenResult result = new GenerateTokenResult();
            result.errorInfo = new ErrorInfo();
            result.errorInfo.errorCode = 0;
            result.errorInfo.errorMessage = "success";

            do
            {
                if (appID == 0)
                {
                    result.errorInfo.errorCode = ErrorCode.appIDInvalid;
                    result.errorInfo.errorMessage = "appID invalid";
                    break;
                }


                if (userID == null)
                {
                    result.errorInfo.errorCode = ErrorCode.userIDInvalid;
                    result.errorInfo.errorMessage = "userID invalid";
                    break;
                }

                if (secret.Length != 32)
                {
                    result.errorInfo.errorCode = ErrorCode.secretInvalid;
                    result.errorInfo.errorMessage = "secret must be a 32 byte string";
                    break;
                }

                if (effectiveTimeInSeconds <= 0)
                {
                    result.errorInfo.errorCode = ErrorCode.effectiveTimeInSecondsInvalid;
                    result.errorInfo.errorMessage = "effectiveTimeInSeconds invalid";
                    break;
                }

                Dictionary<string, object> thirdToken = MakeThirdToken(appID, userID, effectiveTimeInSeconds, payload);

                string strPlaintText = JsonConvert.SerializeObject(thirdToken);

                byte[] nonce = new byte[12]; // GCM 推荐的 nonce 大小
                RandomNumberGenerator.Fill(nonce);

                byte[] encrypt = AesGCMEncrypt(strPlaintText, secret, nonce);

                if (encrypt == null) return null;

                int resultSize = encrypt.Length + nonce.Length + 13;
                byte[] resultBuffer = new byte[resultSize];

                int start = 0;
                //
                start = PackInt64(ref resultBuffer, start, (long)thirdToken["expire"]);
                //
                start = PackByteArray(ref resultBuffer, start, nonce);
                //
                start = PackByteArray(ref resultBuffer, start, encrypt);
                //
                start = PackInt8(ref resultBuffer, start, (byte)AesEncryptMode.AesEncryptModeGCM);

                result.token = "04" + Convert.ToBase64String(resultBuffer, 0, resultSize);
            } while (false);

            return result;
        }

        private static Dictionary<string, object> MakeThirdToken(uint appID, string userID, long effectiveTimeInSeconds, string payload)
        {
            Dictionary<string, object> thirdToken = new Dictionary<string, object>();
            thirdToken["app_id"] = appID;
            thirdToken["user_id"] = userID;
            //thirdToken["payload"] = new Dictionary<string, object>();
            thirdToken["payload"] = payload;

            TimeSpan ts = DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, 0);
            long create_time = Convert.ToInt64(ts.TotalSeconds);

            thirdToken["ctime"] = create_time;
            thirdToken["expire"] = create_time + effectiveTimeInSeconds;

            Random ra = new Random(unchecked((int)DateTime.Now.Ticks));
            long nonce = ra.Next(0, 0x7fffffff);
            thirdToken["nonce"] = nonce;

            return thirdToken;
        }

        private static string MakeRandomString(int length)
        {
            string strRandom = "";

            string str = "0123456789abcdefghijklmnopqrstuvwxyz";

            Random ra = new Random(unchecked((int)DateTime.Now.Ticks));

            for (int i = 0; i < length; i++)
            {
                strRandom += str[ra.Next(0, str.Length)];
            }

            return strRandom;
        }

        private static Byte[] AesGCMEncrypt(string str, string key, byte[] nonce)
        {
            if (string.IsNullOrEmpty(str)) 
            {
                return null;
            }

            byte[] toEncryptArray = Encoding.UTF8.GetBytes(str);
            byte[] keyBytes = Encoding.UTF8.GetBytes(key);
            byte[] cipherText = new byte[toEncryptArray.Length];
            byte[] tag = new byte[16]; // GCM 标签大小为 16 字节

            using (AesGcm aesGcm = new AesGcm(keyBytes))
            {
                aesGcm.Encrypt(nonce, toEncryptArray, cipherText, tag);
            }

            // 合并密文和标签
            byte[] result = new byte[cipherText.Length + tag.Length];
            Buffer.BlockCopy(cipherText, 0, result, 0, cipherText.Length);
            Buffer.BlockCopy(tag, 0, result, cipherText.Length, tag.Length);
            return result;
        }

        private static int PackInt8(ref byte[] result, int start, byte value)
        {
            result[start] = value;
            return start + 1;
        }


        private static int PackInt16(ref byte[] result, int start, short value)
        {
            byte[] data = BitConverter.GetBytes(value);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(data);
            Buffer.BlockCopy(data, 0, result, start, sizeof(short));
            return start + sizeof(short);
        }

        private static int PackInt64(ref byte[] result, int start, long value)
        {
            byte[] data = BitConverter.GetBytes(value);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(data);
            Buffer.BlockCopy(data, 0, result, start, sizeof(Int64));
            return start + sizeof(Int64);
        }

        private static int PackString(ref byte[] result, int start, string value)
        {
            start = PackInt16(ref result, start, (short)value.Length);
            Buffer.BlockCopy(System.Text.Encoding.Default.GetBytes(value), 0, result, start, value.Length);
            return start + value.Length;
        }

        private static int PackByteArray(ref byte[] result, int start, byte[] value)
        {
            start = PackInt16(ref result, start, (short)value.Length);
            Buffer.BlockCopy(value, 0, result, start, value.Length);
            return start + value.Length;
        }
    }
}
