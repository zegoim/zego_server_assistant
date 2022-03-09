package token04_rtcroom

import (
	"encoding/json"

	"github.com/zegoim/zego_server_assistant/token/go/src/errors"
	"github.com/zegoim/zego_server_assistant/token/go/src/token04"
)

const (
	PrivilegeKeyLogin   = 1 // 登录
	PrivilegeKeyPublish = 2 // 推流
	PrivilegeEnable     = 1 // 开启
	PrivilegeDisable    = 0 // 关闭
)

type RtcRoomPayLoad struct {
	RoomId       string      `json:"room_id"`
	Privilege    map[int]int `json:"privilege"`
	StreamIdList []string    `json:"stream_id_list"`
}

func GenerateToken04ForRtcRoom(appId uint32, roomId, userId string, privilege map[int]int, secret string, effectiveTimeInSeconds int64, streamIdList []string) (string, error) {
	if appId == 0 {
		return "", errors.NewZegoSDKError(errors.InvalidParamErrorCode, "appId Invalid")
	}
	if roomId == "" {
		return "", errors.NewZegoSDKError(errors.InvalidParamErrorCode, "roomId Invalid")
	}
	if userId == "" {
		return "", errors.NewZegoSDKError(errors.InvalidParamErrorCode, "userId Invalid")
	}
	if len(secret) != 32 {
		return "", errors.NewZegoSDKError(errors.InvalidParamErrorCode, "secret Invalid")
	}
	if effectiveTimeInSeconds <= 0 {
		return "", errors.NewZegoSDKError(errors.InvalidParamErrorCode, "effectiveTimeInSeconds Invalid")
	}

	payloadData := &RtcRoomPayLoad{
		RoomId:       roomId,
		Privilege:    privilege,
		StreamIdList: streamIdList,
	}

	payload, err := json.Marshal(payloadData)
	if err != nil {
		return "", errors.NewZegoSDKError(errors.JsonMarshalErrorCode, err.Error())
	}

	return token04.GenerateToken04(appId, userId, secret, effectiveTimeInSeconds, string(payload))
}
