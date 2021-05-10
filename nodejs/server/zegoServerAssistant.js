"use strict";
exports.__esModule = true;
var crypto_1 = require("crypto");
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
function getToken(appId, roomId, userId, privilege, secret, effectiveTimeInSeconds) {
    if (!appId) {
        throw new Error('appId required');
    }
    else if (typeof appId !== 'number') {
        throw new Error('appId is not number');
    }
    if (!roomId) {
        throw new Error('roomId required');
    }
    else if (typeof roomId !== 'string') {
        throw new Error('roomId is not string');
    }
    if (!userId) {
        throw new Error('userId required');
    }
    else if (typeof userId !== 'string') {
        throw new Error('userId is not string');
    }
    if (!secret) {
        throw new Error('secret required');
    }
    else if (typeof secret !== 'string') {
        throw new Error('secret is not string');
    }
    else if (secret.length !== 32) {
        throw new Error('secret must 32 byte length string');
    }
    if (!privilege) {
        throw new Error('privilege required');
    }
    else if (typeof privilege !== 'object') {
        throw new Error('privilege format error');
    }
    else if (typeof privilege[1] !== 'number' || typeof privilege[2] !== 'number') {
        throw new Error('privilege key must include 1 and 2; the value must be number');
    }
    if (!effectiveTimeInSeconds) {
        throw new Error('effectiveTimeInSeconds required');
    }
    else if (typeof secret !== 'string') {
        throw new Error('effectiveTimeInSeconds is not number');
    }
    var createTime = Math.floor(new Date().getTime() / 1000);
    var tokenInfo = {
        app_id: appId,
        room_id: roomId,
        user_id: userId,
        privilege: privilege,
        create_time: createTime,
        expire_time: createTime + effectiveTimeInSeconds,
        nonce: makeNonce()
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
exports.getToken = getToken;
