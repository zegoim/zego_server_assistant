package main

import (
	"fmt"
	"github.com/zegoim/zego_server_assistant/token/go/src/token04"
)

/*
基础鉴权token生成示例代码
*/

func main() {
	// 请将 appId 修改为你的 appId，appid 为数字，从即构控制台获取
	// 举例：1234567890
	var appId uint32 = 1234567890

	// 请修改为你的 serverSecret，serverSecret 为字符串，从即构控制台获取
	// 举例： "fa94dd0f974cf2e293728a526b028271"
	serverSecret := ""

	// 请将 userId 修改为用户的 user_id                              
	userId := "user1"

	// token 的有效时长，单位：秒
	var effectiveTimeInSeconds int64 = 3600
	// token业务认证扩展，基础鉴权token此处填空字符串            
	var payload string = ""                            

	//生成token
	token, err := token04.GenerateToken04(appId, userId, serverSecret, effectiveTimeInSeconds, payload)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(token)
}
