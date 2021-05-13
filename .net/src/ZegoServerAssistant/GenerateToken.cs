using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace ZegoServerAssistant
{
    public class ErrorInfo
    {
        public int errorCode;
        public string errorMessage;
    }

    public class GenerateTokenResult
    {
        public string token;
        public ErrorInfo errorInfo;
    }

    public static class GenerateToken
    {
        public static GenerateTokenResult GetToken(uint appID, string roomID, string userID, Dictionary<int, int> privilege, string secret, long effectiveTimeInSeconds)
        {
            GenerateTokenResult result = new GenerateTokenResult();
            result.errorInfo = new ErrorInfo();
            result.errorInfo.errorCode = 0;
            result.errorInfo.errorMessage = "success";

            do
            {
                if (appID == 0)
                {
                    result.errorInfo.errorCode = 1;
                    result.errorInfo.errorMessage = "appID invalid";
                    break;
                }

                if (roomID == null)
                {
                    result.errorInfo.errorCode = 2;
                    result.errorInfo.errorMessage = "roomID invalid";
                    break;
                }

                if (userID == null)
                {
                    result.errorInfo.errorCode = 3;
                    result.errorInfo.errorMessage = "userID invalid";
                    break;
                }

                if (privilege.Count != 2 || !privilege.ContainsKey(1) || !privilege.ContainsKey(2))
                {
                    result.errorInfo.errorCode = 4;
                    result.errorInfo.errorMessage = "privilege key must include 1 and 2; the value must be number";
                    break;
                }

                if (secret.Length != 32)
                {
                    result.errorInfo.errorCode = 5;
                    result.errorInfo.errorMessage = "secret must 32 byte length string";
                    break;
                }

                if (effectiveTimeInSeconds <= 0)
                {
                    result.errorInfo.errorCode = 6;
                    result.errorInfo.errorMessage = "effectiveTimeInSeconds invalid";
                    break;
                }

                Dictionary<string, object> thirdToken = MakeThirdToken(appID, roomID, userID, privilege, effectiveTimeInSeconds);

                string strPlaintText = JsonConvert.SerializeObject(thirdToken);

                string strIv = MakeRandomString(16);

                byte[] encrypt = AesEncrypt(strPlaintText, secret, strIv);

                if (encrypt == null) return null;

                int resultSize = encrypt.Length + 28;
                byte[] resultBuffer = new byte[resultSize];

                //
                PackInt64(ref resultBuffer, 0, (long)thirdToken["expire_time"]);
                //
                PackString(ref resultBuffer, 8, strIv);
                //
                PackByteArray(ref resultBuffer, 26, encrypt);

                result.token = "03" + Convert.ToBase64String(resultBuffer, 0, resultSize);
            } while (false);

            return result;
        }

        private static Dictionary<string, object> MakeThirdToken(uint appID, string roomID, string userID, Dictionary<int, int> privilege, long effectiveTimeInSeconds)
        {
            Dictionary<string, object> thirdToken = new Dictionary<string, object>();
            thirdToken["app_id"] = appID;
            thirdToken["room_id"] = roomID;
            thirdToken["user_id"] = userID;
            thirdToken["privilege"] = new Dictionary<int, int>(privilege);

            TimeSpan ts = DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, 0);
            long create_time = Convert.ToInt64(ts.TotalSeconds);

            thirdToken["create_time"] = create_time;
            thirdToken["expire_time"] = create_time + effectiveTimeInSeconds;

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
