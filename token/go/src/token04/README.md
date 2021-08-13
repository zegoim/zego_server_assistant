# 简介

# 使用说明

## GenerateToken04 参数说明

```go
var appId uint32 = <Your app ID>   // Zego派发的数字ID, 各个开发者的唯一标识
userId := <Your user ID>   //  用户 ID
secret := <Your app certificate>  // 在获取 token 时进行 AES 加密的密钥
var effectiveTimeInSeconds int64 = <Your token effectiveTime>  // token 的有效时长，单位：秒
```


## demo

```go
var appId uint32 = 123
userId := "demo"
secret := "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
var effectiveTimeInSeconds int64 = 3600

token, err := zsa.GenerateToken04(appId, userId, secret, effectiveTimeInSeconds)
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
