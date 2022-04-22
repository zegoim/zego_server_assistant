package main

import (
	"encoding/json"
	"fmt"
	"github.com/zegoim/zego_server_assistant/token/go/src/token04"
)

/*
权限认证token生成示例代码
 */


//token业务扩展：权限认证属性
type RtcRoomPayLoad struct {
	RoomId       string      `json:"room_id"`           //房间id；用于对接口的房间id进行强验证
	Privilege    map[int]int `json:"privilege"`         //权限位开关列表；用于对接口的操作权限进行强验证
	StreamIdList []string    `json:"stream_id_list"`    //流列表；用于对接口的流id进行强验证；允许为空，如果为空，则不对流id验证
}

func main() {
	var appId uint32 = 1                                // Zego派发的数字ID, 各个开发者的唯一标识
	roomId := "demo"                                    // 房间 ID
	userId := "demo"                                    // 用户 ID
	serverSecret := "fa94dd0f974cf2e293728a526b028271"  // 在获取 token 时进行 AES 加密的密钥
	var effectiveTimeInSeconds int64 = 3600             // token 的有效时长，单位：秒

	//请参考 github.com/zegoim/zego_server_assistant/token/go/src/token04/token04.go 定义
	////权限位定义
	//const (
	//	PrivilegeKeyLogin   = 1 // 是否启用登录鉴权
	//	PrivilegeKeyPublish = 2 // 是否启用推流鉴权
	//)

	////权限开关定义
	//const (
	//	PrivilegeEnable     = 1 // 开启
	//	PrivilegeDisable    = 0 // 关闭
	//)

	//业务权限认证配置，可以配置多个权限位
	privilege := make(map[int]int)
	privilege[token04.PrivilegeKeyLogin] = token04.PrivilegeEnable //开启房间登录鉴权
	privilege[token04.PrivilegeKeyPublish] = token04.PrivilegeDisable //关闭推流鉴权

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
