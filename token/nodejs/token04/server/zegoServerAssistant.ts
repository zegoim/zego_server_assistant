import { createCipheriv, randomBytes } from 'crypto';

const enum ErrorCode {
    success = 0, // "success"
    appIDInvalid = 1, // "appID invalid"
    userIDInvalid = 3, // "userID invalid"
    secretInvalid = 5, // "secret must be a 32 byte string"
    effectiveTimeInSecondsInvalid = 6, // "effectiveTimeInSeconds invalid"
}
const enum KPrivilegeKey {
    PrivilegeKeyLogin = 1,
    PrivilegeKeyPublish = 2
}

const enum KPrivilegeVal {
    PrivilegeEnable = 1,
    PrivilegeDisable = 0
}

const enum AesEncryptMode {
    /**
     * AES加密模式: AES/CBC/PKCS5Padding；已废弃
     */
    CBCPKCS5Padding = 0,
    /**
     * AES加密模式: AES/GCM；推荐使用
     */
    GCM = 1
}

interface ErrorInfo {
    errorCode: ErrorCode; // 错误码来自 ErrorCode
    errorMessage: string; // 对错误码的详细描述
}

// 生成 int32 范围的随机数
function makeNonce(): number {
    const min = -Math.pow(2, 31); // -2^31
    const max = Math.pow(2, 31) - 1; // 2^31 - 1
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

// AES加密，使用模式: GCM
function aesGcmEncrypt(plainText: string, key: string): { encryptBuf: Buffer; nonce: Buffer } {
    // 确保密钥长度有效（16、24 或 32 字节）
    if (![16, 24, 32].includes(key.length)) {
        throw createError(ErrorCode.secretInvalid, 'Invalid Secret length. Key must be 16, 24, or 32 bytes.');
    }
    // 随机生成的 12 字节串，用作 AES 加密向量，放在密文前一起做Base64编码生成最终 token
    const nonce = randomBytes(12)
    // console.log('nonce', nonce);
    const cipher = createCipheriv('aes-256-gcm', key, nonce);
    cipher.setAutoPadding(true);
    const encrypted = cipher.update(plainText, 'utf8');
    const encryptBuf = Buffer.concat([encrypted, cipher.final(), cipher.getAuthTag()]);

    return { encryptBuf, nonce };
}

function createError(errorCode: number, errorMessage: string): ErrorInfo {
    return {
        errorCode,
        errorMessage
    }
}

export function generateToken04(
    appId: number,
    userId: string,
    secret: string,
    effectiveTimeInSeconds: number,
    payload?: string
): string {
    if (!appId || typeof appId !== 'number') {
        throw createError(ErrorCode.appIDInvalid, 'appID invalid');
    }

    if (!userId || typeof userId !== 'string' || userId.length > 64) {
        throw createError(ErrorCode.userIDInvalid, 'userId invalid');

    }

    if (!secret || typeof secret !== 'string' || secret.length !== 32) {
        throw createError(ErrorCode.secretInvalid, 'secret must be a 32 byte string');
    }

    if (!(effectiveTimeInSeconds > 0)) {
        throw createError(ErrorCode.effectiveTimeInSecondsInvalid, 'effectiveTimeInSeconds invalid');
    }

    const VERSION_FLAG = '04'

    const createTime = Math.floor(new Date().getTime() / 1000);
    const tokenInfo = {
        app_id: appId,
        user_id: userId,
        nonce: makeNonce(),
        ctime: createTime,
        expire: createTime + effectiveTimeInSeconds,
        payload: payload || ''
    };

    // 把token信息转成json
    const plaintText = JSON.stringify(tokenInfo);
    console.log('plain text: ', plaintText)


    /// 进行加密
    const { encryptBuf, nonce } = aesGcmEncrypt(plaintText, secret);

    // token 二进制拼接  过期时间 + Base64(nonce长度 + nonce + 加密信息长度 + 加密信息 + 加密模式mode)
    const [b1, b2, b3, b4] = [new Uint8Array(8), new Uint8Array(2), new Uint8Array(2), new Uint8Array(1)];
    new DataView(b1.buffer).setBigInt64(0, BigInt(tokenInfo.expire), false);
    new DataView(b2.buffer).setUint16(0, nonce.byteLength, false);
    new DataView(b3.buffer).setUint16(0, encryptBuf.byteLength, false);
    new DataView(b4.buffer).setUint8(0, AesEncryptMode.GCM);
    const buf = Buffer.concat([
        Buffer.from(b1),
        Buffer.from(b2),
        Buffer.from(nonce),
        Buffer.from(b3),
        Buffer.from(encryptBuf),
        Buffer.from(b4),
    ]);
    const dv = new DataView(Uint8Array.from(buf).buffer);
    // 打包数据
    // console.log('-----------------');
    // console.log('-------getBigInt64----------', dv.getBigInt64(0));
    // console.log('-----------------');
    // console.log('-------getUint16----------', dv.getUint16(8));
    // console.log('-----------------');
    return VERSION_FLAG + Buffer.from(dv.buffer).toString('base64');
}
