package main

import (
	"fmt"
	"github.com/zegoim/zego_server_assistant/token/go/src/token04"
)

/*
基础鉴权token生成示例代码
*/

func main() {
	var appId uint32 = 1
	userId := "demo"
	serverSecret := "fa94dd0f974cf2e293728a526b028271"
	var effectiveTimeInSeconds int64 = 3600
	var payload string = ""

	token, err := token04.GenerateToken04(appId, userId, serverSecret, effectiveTimeInSeconds, payload)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(token)
}
