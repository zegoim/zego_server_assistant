ntroduction

# Instructions

## Import the file, and add the file to the python search path

```python
from src import zego_server_assistant
```

## Room privileges description

```python
k_PRIVILEGE_LOGIN = 1      # The "key" value of the dict in the privilege class, used to determine whether the user has the privilege to log in to a room;
                           # "value” : 0 means deny, 1 means allow.
k_PRIVILEGE_PUBLISH = 2    # The "key" value of the dict in the privilege class, used to determine whether the user has the privilege to publish streams;
                           # "value" : 0 means deny, 1 means allow.
```

## Error codes

```python
ERROR_CODE_SUCCESS = 0                   # Token for authentication obtained successfully.
ERROR_CODE_APP_ID_INVALID = 1            # App ID parameter is invalid.
ERROR_CODE_ROOM_ID_INVALID = 2           # Room ID parameter is invalid.
ERROR_CODE_USER_ID_INVALID = 3           # User ID parameter is invalid.
ERROR_CODE_PRIVILEGE_ID_INVALID = 4      # Privilege parameter is invalid.
ERROR_CODE_SECRET_INVALID = 5            # Secret parameter is invalid.
ERROR_CODE_EFFECTIVE_TIME_IN_SECONDS_INVALID = 6  # effectiveTimeInSeconds parameter is invalid.
```

## GenerateToken parameters description and return codes

```python
# Parameters
uint32_t app_id  # App ID assigned by ZEGO, the unique identifier of user.
std::string room_id  # Room ID
std::string user_id  # User ID
std::map<int, int> privilege # Room privilege
std::string secret   # The secret key for AES encryption when applying for token.
std::string effective_time_in_seconds  # The validity period of token, unit: second

# Return codes
TokenInfo  # three members: token, error_code, error_message 
```

## demo

```python
if __name__ == '__main__':
    token_info = zego_server_assistant.generate_token(2913569222, "demo", "demo", {
          1 : 1, 2 : 1}, "b0d996aecc46ad51600ea853bb378c18", 3600)
    print([token_info.token, token_info.error_code, token_info.error_message])
```

# Instructions of integrating the SDK

##  Import the codes 

1. Go to [Github - zego_server_assistant](https://github.com/zegoim/zego_server_assistant) to download the latest codes.
2. Install the module `Crypto.Cipher` for AES encryption.

   ```shell
   pip3 install pycryptodome // Note: Crypto file may be changed to crypto, you need to change it to Crypto manually.

   ```
3. Import `src.zego_server_assistant` and use it according to described above.
