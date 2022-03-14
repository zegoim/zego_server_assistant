# Introduction

# Instructions

## GenerateToken parameters description

```go
var appId uint32 = <Your app ID>   // App ID assigned by ZEGO, the unique identifier of user.
userId := <Your user ID>   //  User ID
secret := <Your app certificate>  // The secret key for AES encryption when applying for token.
var effectiveTimeInSeconds int64 = <Your token effectiveTime>  // The validity period of token, unit: second
var payload string = <Your payload data> //custom data
```


## general token generate demo 
- The general token is used for simple authorization of service interfaces, and the payload field can be empty.

```go
var appId uint32 = 123
userId := "demo"
secret := "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
var payload string = "payload"

token, err := zsa.GenerateToken04(appId, userId, secret, effectiveTimeInSeconds, payload)
if err != nil {
    fmt.Println(err)
    return
}
fmt.Println(token)
```

## strict token generate demo
- The strict token is used in scenarios where strong authentication is required for login-room/push-stream/pull-stream permissions. The payload field should be generated according to the specifications.

```go
var appId uint32 = 123
roomId := "demo"
userId := "demo"
serverSecret := "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
var effectiveTimeInSeconds int64 = 3600
privilege := make(map[int]int)
privilege[token04.PrivilegeKeyLogin] = token04.PrivilegeEnable
privilege[token04.PrivilegeKeyPublish] = token04.PrivilegeDisable

payloadData := &RtcRoomPayLoad{
    RoomId:       roomId,
    Privilege:    privilege,
    StreamIdList: nil,
}

payload, err := json.Marshal(payloadData)
    if err != nil {
    fmt.Println(err)
    return
}

token, err := token04.GenerateToken04(appId, userId, serverSecret, effectiveTimeInSeconds, string(payload))
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