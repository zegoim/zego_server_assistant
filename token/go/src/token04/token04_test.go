package token04

import (
	"testing"
)

func Test_GenerateToken03(t *testing.T) {
	var appId uint32 = 1
	userId := "demo"
	serverSecret := "fa94dd0f974cf2e293728a526b028271"
	var effectiveTimeInSeconds int64 = 3600
	var payload string = ""

	token, err := GenerateToken04(appId, userId, serverSecret, effectiveTimeInSeconds, payload)
	if err != nil {
		t.Error(err)
		return
	}
	t.Log(token)
}
