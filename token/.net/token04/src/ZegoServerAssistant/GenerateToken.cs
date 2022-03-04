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

                string strIv = MakeRandomString(16);

                byte[] encrypt = AesEncrypt(strPlaintText, secret, strIv);

                if (encrypt == null) return null;

                int resultSize = encrypt.Length + 28;
                byte[] resultBuffer = new byte[resultSize];

                //
                PackInt64(ref resultBuffer, 0, (long)thirdToken["expire"]);
                //
                PackString(ref resultBuffer, 8, strIv);
                //
                PackByteArray(ref resultBuffer, 26, encrypt);

                result.token = "04" + Convert.ToBase64String(resultBuffer, 0, resultSize);
            } while (false);

            return result;
        }

        private static Dictionary<string, object> MakeThirdToken(uint appID, string userID, long effectiveTimeInSeconds, string playload)
        {
            Dictionary<string, object> thirdToken = new Dictionary<string, object>();
            thirdToken["app_id"] = appID;
            thirdToken["user_id"] = userID;
            //thirdToken["payload"] = new Dictionary<string, object>();
            thirdToken["payload"] = playload;

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

        private static Byte[] AesEncrypt(string str, string key, string iv)
        {
            if (string.IsNullOrEmpty(str)) return null;
            Byte[] toEncryptArray = Encoding.UTF8.GetBytes(str);

            RijndaelManaged rm = new RijndaelManaged
            {
                Key = Encoding.UTF8.GetBytes(key),
                IV = Encoding.UTF8.GetBytes(iv),
                Mode = CipherMode.CBC,
                Padding = PaddingMode.PKCS7
            };
            ICryptoTransform cTransform = rm.CreateEncryptor();
            Byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);
            return resultArray;
        }

        private static void PackInt16(ref byte[] result, int start, short value)
        {
            byte[] data = BitConverter.GetBytes(value);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(data);
            Buffer.BlockCopy(data, 0, result, start, sizeof(short));
        }

        private static void PackInt64(ref byte[] result, int start, long value)
        {
            byte[] data = BitConverter.GetBytes(value);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(data);
            Buffer.BlockCopy(data, 0, result, start, sizeof(Int64));
        }

        private static void PackString(ref byte[] result, int start, string value)
        {
            PackInt16(ref result, start, (short)value.Length);
            Buffer.BlockCopy(System.Text.Encoding.Default.GetBytes(value), 0, result, start + sizeof(short), value.Length);
        }

        private static void PackByteArray(ref byte[] result, int start, byte[] value)
        {
            PackInt16(ref result, start, (short)value.Length);
            Buffer.BlockCopy(value, 0, result, start + sizeof(short), value.Length);
        }
    }
}
