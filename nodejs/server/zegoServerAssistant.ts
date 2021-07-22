import { createCipheriv } from 'crypto';

enum ErrorCode {
    success = 0, // "success"
    appIDInvalid = 1, // "appID invalid"
    roomIDInvalid = 2, // "roomID invalid"
    userIDInvalid = 3, // "userID invalid"
    privilegeInvalid = 4, // "privilege key must include 1 and 2; the value must be number"
    secretInvalid = 5, // "secret must be a 32 byte string"
    effectiveTimeInSecondsInvalid = 6, // "effectiveTimeInSeconds invalid"
}

interface KPrivilege {
    canLoginRoom: boolean;
    canPublishStream: boolean;
}

interface ErrorInfo {
    errorCode: ErrorCode; // 错误码来自 ErrorCode
    errorMessage: string; // 对错误码的详细描述
}

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

export function generateToken(
    appId: number,
    roomId: string,
    userId: string,
    privilege: KPrivilege,
    secret: string,
    effectiveTimeInSeconds: number,
): string {
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

    if (
        !privilege ||
        typeof privilege !== 'object' ||
        typeof privilege.canLoginRoom !== 'boolean' ||
        typeof privilege.canPublishStream !== 'boolean'
    ) {
        throw {
            errorCode: ErrorCode.privilegeInvalid,
            errorMessage: 'privilege key must include canLoginRoom and canPublishStream; the value must be boolean',
        };
    }

    const _privilege = {
        1: privilege.canLoginRoom ? 1 : 0,
        2: privilege.canPublishStream ? 1 : 0,
    };

    if (!effectiveTimeInSeconds || typeof effectiveTimeInSeconds !== 'number') {
        throw {
            errorCode: ErrorCode.effectiveTimeInSecondsInvalid,
            errorMessage: 'effectiveTimeInSeconds invalid',
        };
    }

    const createTime = Math.floor(new Date().getTime() / 1000);
    const tokenInfo = {
        app_id: appId,
        room_id: roomId,
        user_id: userId,
        privilege: _privilege,
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
