"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.generateToken04 = generateToken04;
var crypto_1 = require("crypto");
// 生成 int32 范围的随机数
function makeNonce() {
    var min = -Math.pow(2, 31); // -2^31
    var max = Math.pow(2, 31) - 1; // 2^31 - 1
    return Math.floor(Math.random() * (max - min + 1)) + min;
}
// AES加密，使用模式: GCM
function aesGcmEncrypt(plainText, key) {
    // 确保密钥长度有效（16、24 或 32 字节）
    if (![16, 24, 32].includes(key.length)) {
        throw createError(5 /* ErrorCode.secretInvalid */, 'Invalid Secret length. Key must be 16, 24, or 32 bytes.');
    }
    // 随机生成的 12 字节串，用作 AES 加密向量，放在密文前一起做Base64编码生成最终 token
    var nonce = (0, crypto_1.randomBytes)(12);
    // console.log('nonce', nonce);
    var cipher = (0, crypto_1.createCipheriv)('aes-256-gcm', key, nonce);
    cipher.setAutoPadding(true);
    var encrypted = cipher.update(plainText, 'utf8');
    var encryptBuf = Buffer.concat([encrypted, cipher.final(), cipher.getAuthTag()]);
    return { encryptBuf: encryptBuf, nonce: nonce };
}
function createError(errorCode, errorMessage) {
    return {
        errorCode: errorCode,
        errorMessage: errorMessage
    };
}
function generateToken04(appId, userId, secret, effectiveTimeInSeconds, payload) {
    if (!appId || typeof appId !== 'number') {
        throw createError(1 /* ErrorCode.appIDInvalid */, 'appID invalid');
    }
    if (!userId || typeof userId !== 'string' || userId.length > 64) {
        throw createError(3 /* ErrorCode.userIDInvalid */, 'userId invalid');
    }
    if (!secret || typeof secret !== 'string' || secret.length !== 32) {
        throw createError(5 /* ErrorCode.secretInvalid */, 'secret must be a 32 byte string');
    }
    if (!(effectiveTimeInSeconds > 0)) {
        throw createError(6 /* ErrorCode.effectiveTimeInSecondsInvalid */, 'effectiveTimeInSeconds invalid');
    }
    var VERSION_FLAG = '04';
    var createTime = Math.floor(new Date().getTime() / 1000);
    var tokenInfo = {
        app_id: appId,
        user_id: userId,
        nonce: makeNonce(),
        ctime: createTime,
        expire: createTime + effectiveTimeInSeconds,
        payload: payload || ''
    };
    // 把token信息转成json
    var plaintText = JSON.stringify(tokenInfo);
    console.log('plain text: ', plaintText);
    /// 进行加密
    var _a = aesGcmEncrypt(plaintText, secret), encryptBuf = _a.encryptBuf, nonce = _a.nonce;
    // token 二进制拼接  过期时间 + Base64(nonce长度 + nonce + 加密信息长度 + 加密信息 + 加密模式mode)
    var _b = [new Uint8Array(8), new Uint8Array(2), new Uint8Array(2), new Uint8Array(1)], b1 = _b[0], b2 = _b[1], b3 = _b[2], b4 = _b[3];
    new DataView(b1.buffer).setBigInt64(0, BigInt(tokenInfo.expire), false);
    new DataView(b2.buffer).setUint16(0, nonce.byteLength, false);
    new DataView(b3.buffer).setUint16(0, encryptBuf.byteLength, false);
    new DataView(b4.buffer).setUint8(0, 1 /* AesEncryptMode.GCM */);
    var buf = Buffer.concat([
        Buffer.from(b1),
        Buffer.from(b2),
        Buffer.from(nonce),
        Buffer.from(b3),
        Buffer.from(encryptBuf),
        Buffer.from(b4),
    ]);
    var dv = new DataView(Uint8Array.from(buf).buffer);
    // 打包数据
    // console.log('-----------------');
    // console.log('-------getBigInt64----------', dv.getBigInt64(0));
    // console.log('-----------------');
    // console.log('-------getUint16----------', dv.getUint16(8));
    // console.log('-----------------');
    return VERSION_FLAG + Buffer.from(dv.buffer).toString('base64');
}
