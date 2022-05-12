package main

import (
	"encoding/json"
	"fmt"
	"github.com/zegoim/zego_server_assistant/token/go/src/token04"
)

/*
权限认证token生成示例代码，使用前需联系即构技术支持开通功能
*/

//token业务扩展：权限认证属性
type RtcRoomPayLoad struct {
	RoomId       string      `json:"room_id"`        //房间id；用于对接口的房间id进行强验证
	Privilege    map[int]int `json:"privilege"`      //权限位开关列表；用于对接口的操作权限进行强验证
	StreamIdList []string    `json:"stream_id_list"` //流列表；用于对接口的流id进行强验证；允许为空，如果为空，则不对流id验证
}

func main() {
	// 请将 appId 修改为你的 appId，appid 为数字，从即构控制台获取
	// 举例：1234567890
	var appId uint32 = 1234567890

	// 请修改为你的 serverSecret，serverSecret 为字符串，从即构控制台获取
	// 举例： "fa94dd0f974cf2e293728a526b028271"
	serverSecret := ""

	// 请将 userId 修改为用户的 user_id                              
	userId := "user1"

	// 请将 roomId 修改为用户的 roomId
	roomId := "room1"                                   
	        
	// token 的有效时长，单位：秒
	var effectiveTimeInSeconds int64 = 3600
	

	//请参考 github.com/zegoim/zego_server_assistant/token/go/src/token04/token04.go 定义
	////权限位定义
	//const (
	//	PrivilegeKeyLogin   = 1 // 1 代表登录权限
	//	PrivilegeKeyPublish = 2 // 2 代表推流权限
	//)

	////权限开关定义
	//const (
	//	PrivilegeEnable     = 1 // 允许相应业务权限
	//	PrivilegeDisable    = 0 // 不允许相应业务权限
	//)

	//业务权限认证配置，可以配置多个权限位
	privilege := make(map[int]int)
	privilege[token04.PrivilegeKeyLogin] = token04.PrivilegeEnable    //允许房间登录
	privilege[token04.PrivilegeKeyPublish] = token04.PrivilegeDisable //不允许推流

	//token业务扩展配置
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

	//生成token
	token, err := token04.GenerateToken04(appId, userId, serverSecret, effectiveTimeInSeconds, string(payload))
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(token)
}
