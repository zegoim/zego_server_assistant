package main

import (
	"fmt"
	"github.com/zegoim/zego_server_assistant/token/go/src/token03"
)

func main() {
	var appId uint32 = 1
	roomId := "demo"
	userId := "demo"
	serverSecret := "fa94dd0f974cf2e293728a526b028271"
	var effectiveTimeInSeconds int64 = 3600
	privilege := make(map[int]int)
	privilege[token03.PrivilegeKeyLogin] = token03.PrivilegeEnable
	privilege[token03.PrivilegeKeyPublish] = token03.PrivilegeDisable

	token, err := token03.GenerateToken03(appId, roomId, userId, privilege, serverSecret, effectiveTimeInSeconds)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(token)
}
