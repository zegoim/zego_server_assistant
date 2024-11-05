#!/usr/bin/env python -u
# coding:utf-8
import json
import random
import time
import struct
import binascii
from Crypto.Cipher import AES

ERROR_CODE_SUCCESS = 0                              # 获取鉴权 token 成功
ERROR_CODE_APP_ID_INVALID = 1                       # 调用方法时传入 appID 参数错误
ERROR_CODE_USER_ID_INVALID = 3                      # 调用方法时传入 userID 参数错误
ERROR_CODE_SECRET_INVALID = 5                       # 调用方法时传入 secret 参数错误
ERROR_CODE_EFFECTIVE_TIME_IN_SECONDS_INVALID = 6    # 调用方法时传入 effective_time_in_seconds 参数错误


class TokenInfo:
    def __init__(self, token, error_code, error_message):
        self.token = token
        self.error_code = error_code
        self.error_message = error_message


def __make_nonce():
    # 生成一个 12 字节的随机 nonce (IV)，返回字符串形式
    str_chars = '0123456789abcdefghijklmnopqrstuvwxyz'
    return ''.join(random.choice(str_chars) for _ in range(12))

def __aes_gcm_with_tag_encrypy(plain_text, key, iv):
    cipher = AES.new(key.encode('utf-8'), AES.MODE_GCM, nonce=iv.encode('utf-8'))
    ciphertext, tag = cipher.encrypt_and_digest(plain_text.encode('utf-8'))
    return ciphertext, tag
     
def generate_token04(app_id, user_id, secret, effective_time_in_seconds, payload):
    '''基本描述
        获取 token 的方法
    详细描述

    Args:
        app_id: Zego派发的数字ID, 各个开发者的唯一标识
        user_id: 用户ID
        secret: 在鉴权 token 计算过程中 AES 加密需要的密钥,32字节的字符串
        effective_time_in_seconds token: 的有效时长，单位：秒
        payload:有效载荷

    Returns:
        TokenInfo: 包含三个对象，token, error_code, error_message
    '''

    if type(app_id) != int or app_id == 0:
        return TokenInfo("", ERROR_CODE_APP_ID_INVALID, "appID invalid")
    if type(user_id) != str or user_id == "":
        return TokenInfo("", ERROR_CODE_USER_ID_INVALID, "userID invalid")
    if type(secret) != str or len(secret) != 32:
        return TokenInfo("", ERROR_CODE_SECRET_INVALID, "secret must be a 32 byte string")
    if type(effective_time_in_seconds) != int or effective_time_in_seconds <= 0:
        return TokenInfo("", ERROR_CODE_EFFECTIVE_TIME_IN_SECONDS_INVALID, "effective_time_in_seconds invalid")
    create_time = int(time.time())
    expire_time = create_time + effective_time_in_seconds
    #生成一个随机数
    random_int = random.randint(1, 90000000)

    _token = {"app_id": app_id, "user_id": user_id, "nonce": random_int,
              "ctime": create_time, "expire": expire_time, "payload": payload}
    plain_text = json.dumps(_token, separators=(',', ':'), ensure_ascii=False)
    
    #生成一个12字节的用于aes 加密的once
    nonce = __make_nonce()
    ciphertext, tag =  __aes_gcm_with_tag_encrypy(plain_text, secret, nonce)

    #aes 的tag  需要接在buf 后面
    encrypt_buf = bytearray(len(ciphertext) + len(tag))
    encrypt_buf[0: 0 + len(ciphertext)] = ciphertext[:]
    encrypt_buf[len(ciphertext):len(ciphertext)+ len(tag)] = tag[:]

    result_size = len(encrypt_buf) + 24  # 结果大小要加上加密数据的长度
    result = bytearray(result_size)

    # 处理过期时间
    big_endian_expire_time = struct.pack("!q", expire_time)
    result[0: 0 + len(big_endian_expire_time)] = big_endian_expire_time[:]

    # 处理 nonce 长度和内容
    big_endian_once_size = struct.pack("!h", len(nonce))
    result[8: 8 + len(big_endian_once_size)] = big_endian_once_size[:]

    buffer = bytearray(nonce.encode('utf-8'))
    result[10: 10 + len(buffer)] = buffer[:]

    # 处理加密数据
    big_endian_buf_size = struct.pack("!h", len(encrypt_buf))
    result[22: 22 + len(big_endian_buf_size)] = big_endian_buf_size[:]
    result[24: 24 + len(encrypt_buf)] = encrypt_buf[:]

    # append mode token use gcm
    AesEncryptModeGCM = 1
    result.append(AesEncryptModeGCM)

    # 将结果进行 Base64 编码
    token = "04" + binascii.b2a_base64(result, newline=False).decode()

    return TokenInfo(token, ERROR_CODE_SUCCESS, "success")
