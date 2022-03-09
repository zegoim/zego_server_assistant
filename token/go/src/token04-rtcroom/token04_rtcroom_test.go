package token04_rtcroom

import (
	"testing"
)

func Test_GenerateToken03(t *testing.T) {
	var appId uint32 = 1
	roomId := "demo"
	userId := "demo"
	serverSecret := "fa94dd0f974cf2e293728a526b028271"
	var effectiveTimeInSeconds int64 = 3600
	privilege := make(map[int]int)
	privilege[PrivilegeKeyLogin] = PrivilegeEnable
	privilege[PrivilegeKeyPublish] = PrivilegeDisable

	token, err := GenerateToken04ForRtcRoom(appId, roomId, userId, privilege, serverSecret, effectiveTimeInSeconds, nil)
	if err != nil {
		t.Error(err)
		return
	}
	t.Log(token)
}
