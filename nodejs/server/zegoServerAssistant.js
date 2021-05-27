"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var crypto_1 = require("crypto");
var ErrorCode;
(function (ErrorCode) {
    ErrorCode[ErrorCode["success"] = 0] = "success";
    ErrorCode[ErrorCode["appIDInvalid"] = 1] = "appIDInvalid";
    ErrorCode[ErrorCode["roomIDInvalid"] = 2] = "roomIDInvalid";
    ErrorCode[ErrorCode["userIDInvalid"] = 3] = "userIDInvalid";
    ErrorCode[ErrorCode["privilegeInvalid"] = 4] = "privilegeInvalid";
    ErrorCode[ErrorCode["secretInvalid"] = 5] = "secretInvalid";
    ErrorCode[ErrorCode["effectiveTimeInSecondsInvalid"] = 6] = "effectiveTimeInSecondsInvalid";
})(ErrorCode || (ErrorCode = {}));
function makeNonce() {
    return Date.now();
}
function makeRandomIv() {
    var str = '0123456789abcdefghijklmnopqrstuvwxyz';
    var result = [];
    for (var i = 0; i < 16; i++) {
        var r = Math.floor(Math.random() * str.length);
        result.push(str.charAt(r));
    }
    return result.join('');
}
// 根据密钥长度确定算法, 只支持16 24 32 位
function getAlgorithm(keyBase64) {
    var key = Buffer.from(keyBase64);
    switch (key.length) {
        case 16:
            return 'aes-128-cbc';
        case 24:
            return 'aes-192-cbc';
        case 32:
            return 'aes-256-cbc';
    }
    throw new Error('Invalid key length: ' + key.length);
}
// AES加密，使用模式: CBC/PKCS5Padding
function aesEncrypt(plainText, key, iv) {
    var cipher = crypto_1.createCipheriv(getAlgorithm(key), key, iv);
    cipher.setAutoPadding(true);
    var encrypted = cipher.update(plainText);
    var final = cipher.final();
    var out = Buffer.concat([encrypted, final]);
    return Uint8Array.from(out).buffer;
}
function generateToken(appId, roomId, userId, privilege, secret, effectiveTimeInSeconds) {
    if (!appId || typeof appId !== 'number') {
        throw {
            errorCode: ErrorCode.appIDInvalid,
            errorMessage: 'appID invalid',
        };
    }
    if (!roomId || typeof roomId !== 'string') {
        throw {
            errorCode: ErrorCode.roomIDInvalid,
            errorMessage: 'roomID invalid',
        };
    }
    if (!userId || typeof userId !== 'string') {
        throw {
            errorCode: ErrorCode.userIDInvalid,
            errorMessage: 'userId invalid',
        };
    }
    if (!secret || typeof secret !== 'string' || secret.length !== 32) {
        throw {
            errorCode: ErrorCode.secretInvalid,
            errorMessage: 'secret must be a 32 byte string',
        };
    }
    if (!privilege ||
        typeof privilege !== 'object' ||
        typeof privilege.canLoginRoom !== 'boolean' ||
        typeof privilege.canPublishStream !== 'boolean') {
        throw {
            errorCode: ErrorCode.privilegeInvalid,
            errorMessage: 'privilege key must include canLoginRoom and canPublishStream; the value must be boolean',
        };
    }
    var _privilege = {
        1: privilege.canLoginRoom ? 1 : 0,
        2: privilege.canPublishStream ? 1 : 0,
    };
    if (!effectiveTimeInSeconds || typeof effectiveTimeInSeconds !== 'number') {
        throw {
            errorCode: ErrorCode.effectiveTimeInSecondsInvalid,
            errorMessage: 'effectiveTimeInSeconds invalid',
        };
    }
    var createTime = Math.floor(new Date().getTime() / 1000);
    var tokenInfo = {
        app_id: appId,
        room_id: roomId,
        user_id: userId,
        privilege: _privilege,
        create_time: createTime,
        expire_time: createTime + effectiveTimeInSeconds,
        nonce: makeNonce(),
    };
    // 把token信息转成json
    var plaintText = JSON.stringify(tokenInfo);
    // 随机生成的 16 字节串，用作 AES 加密向量，放在密文前一起做Base64编码生成最终 token
    var iv = makeRandomIv();
    console.log('iv', iv);
    /// 进行加密
    var encryptBuf = aesEncrypt(plaintText, secret, iv);
    // token 二进制拼接  过期时间 + Base64(iv长度 + iv + 加密信息长度 + 加密信息)
    var _a = [new Uint8Array(8), new Uint8Array(2), new Uint8Array(2)], b1 = _a[0], b2 = _a[1], b3 = _a[2];
    new DataView(b1.buffer).setBigInt64(0, BigInt(tokenInfo.expire_time), false);
    new DataView(b2.buffer).setUint16(0, iv.length, false);
    new DataView(b3.buffer).setUint16(0, encryptBuf.byteLength, false);
    var buf = Buffer.concat([
        Buffer.from(b1),
        Buffer.from(b2),
        Buffer.from(iv),
        Buffer.from(b3),
        Buffer.from(encryptBuf),
    ]);
    var dv = new DataView(Uint8Array.from(buf).buffer);
    // 打包数据
    // console.log('-----------------');
    // console.log('-------getBigInt64----------', dv.getBigInt64(0));
    // console.log('-----------------');
    // console.log('-------getUint16----------', dv.getUint16(8));
    // console.log('-----------------');
    return '03' + Buffer.from(dv.buffer).toString('base64');
}
exports.generateToken = generateToken;
var secret = 'b0d996aecc46ad51600ea853bb378c18';
var token = generateToken(2913569222, '127', 'zhaowei', { canLoginRoom: true, canPublishStream: true }, secret, 3600);
console.log(token);
