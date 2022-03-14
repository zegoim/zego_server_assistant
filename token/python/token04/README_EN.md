Introduction

# Instructions

## Import the file, and add the file to the python search path

```python
from src import token04
```

## Error codes

```python
ERROR_CODE_SUCCESS = 0                   # Token for authentication obtained successfully.
ERROR_CODE_APP_ID_INVALID = 1            # App ID parameter is invalid.
ERROR_CODE_USER_ID_INVALID = 3           # User ID parameter is invalid.
ERROR_CODE_SECRET_INVALID = 5            # Secret parameter is invalid.
ERROR_CODE_EFFECTIVE_TIME_IN_SECONDS_INVALID = 6  # effectiveTimeInSeconds parameter is invalid.
```

## GenerateToken parameters description and return codes

```python
# Parameters
app_id:int  # App ID assigned by ZEGO, the unique identifier of user.
user_id:str  # User ID
secret:str   # The secret key for AES encryption when applying for token.
effective_time_in_seconds:int  # The validity period of token, unit: second

# Return codes
token:TokenInfo  # three members: token, error_code, error_message 
```

## general token generate demo 
- The general token is used for simple authorization of service interfaces, and the payload field can be empty.

```python
if __name__ == '__main__':
    token_info = zego_server_assistant.generate_token04(2913569222, "demo", "b0d996aecc46ad51600ea853bb378c18", 3600, "")
    print([token_info.token, token_info.error_code, token_info.error_message])
```

## strict token generate demo
- The strict token is used in scenarios where strong authentication is required for login-room/push-stream/pull-stream permissions. The payload field should be generated according to the specifications.

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

# Instructions of integrating the SDK

##  Import the codes 

1. Go to [Github - zego_server_assistant](https://github.com/zegoim/zego_server_assistant) to download the latest codes.
2. Install the module `Crypto.Cipher` for AES encryption.

   ```shell
   pip3 install pycryptodome // Note: Crypto file may be changed to crypto, you need to change it to Crypto manually.

   ```
3. Import `src.token04` and use it according to described above.
