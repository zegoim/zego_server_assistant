# 简介

# 使用说明

## 需要引入的头文件、命名空间

```c#
using ZegoServerAssistant;
using Newtonsoft.Json;
```


## 错误码说明

```c#
public enum ErrorCode
{
	success = 0,  				// 获取鉴权 token 成功
	appIDInvalid = 1,   				// 调用方法时传入 appID 参数错误
	userIDInvalid = 3,  				// 调用方法时传入 userID 参数错误
	secretInvalid = 5,  				// 调用方法时传入 secret 参数错误
	effectiveTimeInSecondsInvalid = 6  	// 调用方法时传入 effectiveTimeInSeconds 参数错误
};
```

## GenerateToken04参数及返回值说明

```c#
/**
 * 根据所提供的参数列表生成用于与即构服务端通信的鉴权 token
 * @param appId Zego派发的数字ID, 各个开发者的唯一标识
 * @param userId 用户 ID
 * @param secret 由即构提供的与 appId 对应的密钥，请妥善保管，切勿外泄
 * @param effectiveTimeInSeconds token 的有效时长，单位：秒
 * @return 返回 token 内容，在使用前，请检查 errorInfo 字段是否为 SUCCESS。实际 token 内容保存在 token 字段中
 */
public static GenerateTokenResult GenerateToken04(uint appID, string userID, string secret, long effectiveTimeInSeconds)
```

## demo

```c#
public Form1()
{
		InitializeComponent();

		ZegoServerAssistant.GenerateTokenResult result = ZegoServerAssistant.ServerAssistant.GenerateToken04(1, "111", "12345678900987654321123456789012", 3600);
}
```

# 接入 SDK 说明

## 源码引入方式使用说明

1. 前往 [Github 代码托管地址](https://github.com/zegoim/zego_server_assistant) 下载最新代码。
2. 使用 Visual Studio 打开 ZegoServerAssistant.sln 解决方案生成 ZegoServerAssistant.dll ，然后在您项目中引入此 dll，或者直接将 GenerateToken.cs 源码集成到您项目中。
3. 按照上文使用说明使用 GenerateToken 方法。
