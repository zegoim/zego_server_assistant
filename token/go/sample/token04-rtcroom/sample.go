package main

import (
	"fmt"
	token04_rtcroom "github.com/zegoim/zego_server_assistant/token/go/src/token04-rtcroom"
)

func main() {
	var appId uint32 = 1
	roomId := "demo"
	userId := "demo"
	serverSecret := "fa94dd0f974cf2e293728a526b028271"
	var effectiveTimeInSeconds int64 = 3600
	privilege := make(map[int]int)
	privilege[token04_rtcroom.PrivilegeKeyLogin] = token04_rtcroom.PrivilegeEnable
	privilege[token04_rtcroom.PrivilegeKeyPublish] = token04_rtcroom.PrivilegeDisable

	token, err := token04_rtcroom.GenerateToken04ForRtcRoom(appId, roomId, userId, privilege, serverSecret, effectiveTimeInSeconds, nil)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(token)
}
