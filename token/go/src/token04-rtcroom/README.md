# 简介

# 使用说明
## 房间权限说明
```go
const (
	PrivilegeKeyLogin   = 1  // privilege 中是否允许登录房间的 "key"; "value" : PrivilegeDisable 不允许, PrivilegeEnable 允许
	PrivilegeKeyPublish = 2 // privilege 中是否允许推流的 "key"; "value" : PrivilegeDisable 不允许, PrivilegeEnable 允许
	PrivilegeEnable     = 1 // 允许
	PrivilegeDisable    = 0 // 不允许
)
```



## GenerateToken参数说明

```go
var appId uint32 = <Your app ID>   // Zego派发的数字ID, 各个开发者的唯一标识
roomId := <The channel this token is generated for>  // 房间 ID
userId := <Your user ID>   //  用户 ID
secret := <Your app certificate>  // 在获取 token 时进行 AES 加密的密钥
var effectiveTimeInSeconds int64 = <Your token effectiveTime>  // token 的有效时长，单位：秒
privilege := make(map[int]int) // 房间权限
privilege[zsa.PrivilegeKeyLogin] = zsa.PrivilegeEnable      // 登录权限
privilege[zsa.PrivilegeKeyPublish] = zsa.PrivilegeDisable   // 推流权限
streamIdList := <streamId list> //流列表，默认为空
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

token, err := zsa.GenerateToken04ForRtcRoom(appId, roomId, userId, privilege, secret, effectiveTimeInSeconds, nil)
if err != nil {
    fmt.Println(err)
    return
}
fmt.Println(token)
```

## 源码引入方式使用说明
1. 前往 [Github 代码托管地址](https://github.com/zegoim/zego_server_assistant) 下载最新代码。
2. 将 go/zegoserverassistant 目录 拷贝到 项目中
3. `import zsa "your-project-go-mod-path/zegoserverassistant"`
