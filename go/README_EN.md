# Introduction

# Instructions
## Room privileges description
```go
const (
	PrivilegeKeyLogin   = 1  // The "key" in the privilege class, used to determine whether the user has the privilege to log in to a room; "value" : PrivilegeDisable means deny, PrivilegeEnable means allow.
	PrivilegeKeyPublish = 2 // The "key" in the privilege class, used to determine whether the user has the privilege to publish streams; "value" : PrivilegeDisable means deny, PrivilegeEnable means allow.
	PrivilegeEnable     = 1 // Allow
	PrivilegeDisable    = 0 // Deny
)
```



## GenerateToken parameters description

```go
var appId uint32 = <Your app ID>   // App ID assigned by ZEGO, the unique identifier of user.
roomId := <The channel this token is generated for>  // Room ID
userId := <Your user ID>   //  User ID
secret := <Your app certificate>  // The secret key for AES encryption when applying for token.
var effectiveTimeInSeconds int64 = <Your token effectiveTime>  // The validity period of token, unit: second
privilege := make(map[int]int) // Room privilege
privilege[zsa.PrivilegeKeyLogin] = zsa.PrivilegeEnable      // Login privilege
privilege[zsa.PrivilegeKeyPublish] = zsa.PrivilegeDisable   // Stream publishing privilege
```


## demo

```go
var appId uint32 = 123
roomId := "demo"
userId := "demo"
secret := "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
var effectiveTimeInSeconds int64 = 3600
privilege := make(map[int]int)  
privilege[zsa.PrivilegeKeyLogin] = zsa.PrivilegeEnable      
privilege[zsa.PrivilegeKeyPublish] = zsa.PrivilegeDisable 

token, err := zsa.GenerateToken(appId, roomId, userId, privilege, secret, effectiveTimeInSeconds)
if err != nil {
    fmt.Println(err)
    return
}
fmt.Println(token)
```

## Import the codes 
1. Go to [Github - zego_server_assistant](https://github.com/zegoim/zego_server_assistant) to download the latest codes.
2. Copy the go/zegoserverassistant directory to your project.
3. `import zsa "your-project-go-mod-path/zegoserverassistant"`
{"mode":"full","isActive":false}
