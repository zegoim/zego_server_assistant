# How to use
## Copy & Import
1. 将 go/zegoserverassistant 目录 拷贝到 项目中
2. `import zsa "your-project-go-mod-path/zegoserverassistant"`

## Generate Token
```go
const (
	PrivilegeKeyLogin   = 1 // 登录
	PrivilegeKeyPublish = 2 // 推流
	PrivilegeEnable     = 1 // 开启
	PrivilegeDisable    = 0 // 关闭
)
```

```go
var appId uint32 = <Your app ID>   // type: uint32
roomId := <The channel this token is generated for>  // type: string
userId := <Your user ID>  // type: string
secret := <Your app certificate>  // type: 32 byte length string
var effectiveTimeInSeconds int64 = <Your token effectiveTime> //type: int64; unit: s
privilege := make(map[int]int)
privilege[zsa.PrivilegeKeyLogin] = zsa.PrivilegeEnable      // 登录权限
privilege[zsa.PrivilegeKeyPublish] = zsa.PrivilegeDisable   // 推流权限

token, err := zsa.GenerateToken(appId, roomId, userId, privilege, secret, effectiveTimeInSeconds)
if err != nil {
    fmt.Println(err)
    return
}
fmt.Println(token)
```
