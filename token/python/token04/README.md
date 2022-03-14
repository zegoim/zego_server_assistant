简介

# 使用说明

## 引入文件，并将文件加入 python 搜索路径

```python
from src import token04
```

## 错误码说明

```python
ERROR_CODE_SUCCESS = 0                   # 获取鉴权 token 成功
ERROR_CODE_APP_ID_INVALID = 1            # 调用方法时传入 app_id 参数错误
ERROR_CODE_USER_ID_INVALID = 3           # 调用方法时传入 user_id 参数错误
ERROR_CODE_SECRET_INVALID = 5            # 调用方法时传入 secret 参数错误
ERROR_CODE_EFFECTIVE_TIME_IN_SECONDS_INVALID = 6  # 调用方法时传入 effective_time_in_seconds 参数错误
```

## GenerateToken04 参数及返回值说明

```python
# 参数
app_id:int  # Zego派发的数字ID, 各个开发者的唯一标识
user_id:str  # 用户 ID
secret:str   # 在获取 token 时进行 AES 加密的密钥
effective_time_in_seconds:int  # token 的有效时长，单位：秒
有效载荷:有效载荷

# 返回值
token:TokenInfo  # 三个成员: token, error_code, error_message 
```

## 普通token 生成demo
- 普通token用于服务接口的简单权限验证的场景，payload字段可传空

```python
if __name__ == '__main__':
    token_info = zego_server_assistant.generate_token04(2913569222, "demo", "b0d996aecc46ad51600ea853bb378c18", 3600, "")
    print([token_info.token, token_info.error_code, token_info.error_message])
```

## 强验证token 生成demo
- 强验证token用于对房间登录/推拉流权限需要进行强验证的场景，payload字段需要按照规格生成

```python
if __name__ == '__main__':
    payload = {
        "room_id": "demo",
        "privilege": {1 : 1, 2 : 1},
        "stream_id_list": None
    }
    token_info = zego_server_assistant.generate_token04(app_id=1, user_id="demo", secret="fa94dd0f974cf2e293728a526b028271",
                                                        effective_time_in_seconds=3600, payload=json.dumps(payload))
    print([token_info.token, token_info.error_code, token_info.error_message])
```

# 接入 SDK 说明

## 源码引入方式使用说明

1. 前往 [Github 代码托管地址](https://github.com/zegoim/zego_server_assistant) 下载最新代码。
2. 需要安装模块：`Crypto.Cipher`用于 AES 加密

   ```shell
   pip3 install pycryptodome // 注意：安装后 Crypto 文件夹可能为 crypto，需要手动改回为 Crypto

   ```
3. 引入 `src.token04` 后通过上文使用方法使用
