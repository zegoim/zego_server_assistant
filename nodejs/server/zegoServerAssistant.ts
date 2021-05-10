import { createCipheriv } from 'crypto';
function makeNonce(): number {
    return Date.now();
}

function makeRandomIv(): string {
    const str = '0123456789abcdefghijklmnopqrstuvwxyz';
    const result = [];
    for (let i = 0; i < 16; i++) {
        const r = Math.floor(Math.random() * str.length);
        result.push(str.charAt(r));
    }
    return result.join('');
}

// 根据密钥长度确定算法, 只支持16 24 32 位
function getAlgorithm(keyBase64: string): string {
    const key = Buffer.from(keyBase64);
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
function aesEncrypt(plainText: string, key: string, iv: string): ArrayBuffer {
    const cipher = createCipheriv(getAlgorithm(key), key, iv);
    cipher.setAutoPadding(true);
    const encrypted = cipher.update(plainText);
    const final = cipher.final();
    const out = Buffer.concat([encrypted, final]);

    return Uint8Array.from(out).buffer;
}

export function getToken(
    appId: number,
    roomId: string,
    userId: string,
    privilege: { [index: number]: number },
    secret: string,
    effectiveTimeInSeconds: number,
): string {
    if (!appId) {
        throw new Error('appId required');
    } else if (typeof appId !== 'number') {
        throw new Error('appId is not number');
    }

    if (!roomId) {
        throw new Error('roomId required');
    } else if (typeof roomId !== 'string') {
        throw new Error('roomId is not string');
    }

    if (!userId) {
        throw new Error('userId required');
    } else if (typeof userId !== 'string') {
        throw new Error('userId is not string');
    }

    if (!secret) {
        throw new Error('secret required');
    } else if (typeof secret !== 'string') {
        throw new Error('secret is not string');
    } else if (secret.length !== 32) {
        throw new Error('secret must 32 byte length string');
    }

    if (!privilege) {
        throw new Error('privilege required');
    } else if (typeof privilege !== 'object') {
        throw new Error('privilege format error');
    } else if (typeof privilege[1] !== 'number' || typeof privilege[2] !== 'number') {
        throw new Error('privilege key must include 1 and 2; the value must be number');
    }

    if (!effectiveTimeInSeconds) {
        throw new Error('effectiveTimeInSeconds required');
    } else if (typeof secret !== 'string') {
        throw new Error('effectiveTimeInSeconds is not number');
    }

    const createTime = Math.floor(new Date().getTime() / 1000);
    const tokenInfo = {
        app_id: appId,
        room_id: roomId,
        user_id: userId,
        privilege: privilege,
        create_time: createTime,
        expire_time: createTime + effectiveTimeInSeconds,
        nonce: makeNonce(),
    };

    // 把token信息转成json
    const plaintText = JSON.stringify(tokenInfo);

    // 随机生成的 16 字节串，用作 AES 加密向量，放在密文前一起做Base64编码生成最终 token
    const iv: string = makeRandomIv();
    console.log('iv', iv);

    /// 进行加密
    const encryptBuf = aesEncrypt(plaintText, secret, iv);

    // token 二进制拼接  过期时间 + Base64(iv长度 + iv + 加密信息长度 + 加密信息)
    const [b1, b2, b3] = [new Uint8Array(8), new Uint8Array(2), new Uint8Array(2)];
    new DataView(b1.buffer).setBigInt64(0, BigInt(tokenInfo.expire_time), false);
    new DataView(b2.buffer).setUint16(0, iv.length, false);
    new DataView(b3.buffer).setUint16(0, encryptBuf.byteLength, false);
    const buf = Buffer.concat([
        Buffer.from(b1),
        Buffer.from(b2),
        Buffer.from(iv),
        Buffer.from(b3),
        Buffer.from(encryptBuf),
    ]);
    const dv = new DataView(Uint8Array.from(buf).buffer);
    // 打包数据
    // console.log('-----------------');
    // console.log('-------getBigInt64----------', dv.getBigInt64(0));
    // console.log('-----------------');
    // console.log('-------getUint16----------', dv.getUint16(8));
    // console.log('-----------------');
    return '03' + Buffer.from(dv.buffer).toString('base64');
}
