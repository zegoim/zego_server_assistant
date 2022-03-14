package main

import (
	"encoding/json"
	"fmt"
	"github.com/zegoim/zego_server_assistant/token/go/src/token04"
)

//token业务扩展：RTC房间认证属性
type RtcRoomPayLoad struct {
	RoomId       string      `json:"room_id"`           //房间id；用于对接口的房间id进行强验证
	Privilege    map[int]int `json:"privilege"`         //权限位开关列表；用于对接口的操作权限进行强验证
	StreamIdList []string    `json:"stream_id_list"`    //流列表；用于对接口的流id进行强验证；允许为空，如果为空，则不对流id验证
}

func main() {
	var appId uint32 = 1
	roomId := "demo"
	userId := "demo"
	serverSecret := "fa94dd0f974cf2e293728a526b028271"
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
}
