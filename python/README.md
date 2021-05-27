简介

# 使用说明

## 引入文件，并将文件加入 python 搜索路径

```python
from src import zego_server_assistant
```

## 房间权限说明

```python
k_PRIVILEGE_LOGIN = 1      # privilege 中是否允许登录房间的 "key"; dict 中
                           # 对应的 "value" : 0 不允许, 1 允许
k_PRIVILEGE_PUBLISH = 2    # privilege 中是否允许推流的 "key"; dict 中
                           # 对应的 "value" : 0 不允许, 1 允许S
```

## 错误码说明

```python
ERROR_CODE_SUCCESS = 0                   # 获取鉴权 token 成功
ERROR_CODE_APP_ID_INVALID = 1            # 调用方法时传入 app_id 参数错误
ERROR_CODE_ROOM_ID_INVALID = 2           # 调用方法时传入 room_id 参数错误
ERROR_CODE_USER_ID_INVALID = 3           # 调用方法时传入 user_id 参数错误
ERROR_CODE_PRIVILEGE_ID_INVALID = 4      # 调用方法时传入 privilege 参数错误
ERROR_CODE_SECRET_INVALID = 5            # 调用方法时传入 secret 参数错误
ERROR_CODE_EFFECTIVE_TIME_IN_SECONDS_INVALID = 6  # 调用方法时传入 effective_time_in_seconds 参数错误
```

## GenerateToken参数及返回值说明

```python
# 参数
uint32_t app_id  # Zego派发的数字ID, 各个开发者的唯一标识
std::string room_id  # 房间 ID
std::string user_id  # 用户 ID
std::map<int, int> privilege # 房间权限
std::string secret   # 在获取 token 时进行 AES 加密的密钥
std::string effective_time_in_seconds  # token 的有效时长，单位：秒

# 返回值
TokenInfo  # 三个成员: token, error_code, error_message 
```

## demo

```python
if __name__ == '__main__':
    token_info = zego_server_assistant.generate_token(2913569222, "demo", "demo", {
          1 : 1, 2 : 1}, "b0d996aecc46ad51600ea853bb378c18", 3600)
    print([token_info.token, token_info.error_code, token_info.error_message])
```

# 接入 SDK 说明

## 源码引入方式使用说明

1. 前往 [Github 代码托管地址](https://github.com/zegoim/zego_server_assistant) 下载最新代码。
2. 需要安装模块：`Crypto.Cipher`用于 AES 加密

   ```shell
   pip3 install pycryptodome // 注意：安装后 Crypto 文件夹可能为 crypto，需要手动改回为 Crypto

   ```
3. 引入 `src.zego_server_assistant`后通过上文使用方法使用
