package main

import (
	"fmt"
	"github.com/zegoim/zego_server_assistant/token/go/src/token04"
)

/*
基础鉴权token生成示例代码
*/

func main() {
	var appId uint32 = 1                               // Zego派发的数字ID, 各个开发者的唯一标识
	userId := "demo"                                   // 用户 ID
	serverSecret := "fa94dd0f974cf2e293728a526b028271" // 在获取 token 时进行 AES 加密的密钥
	var effectiveTimeInSeconds int64 = 3600            // token 的有效时长，单位：秒
	var payload string = ""                            // token业务认证扩展，基础鉴权token此处填空

	//生成token
	token, err := token04.GenerateToken04(appId, userId, serverSecret, effectiveTimeInSeconds, payload)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(token)
}
