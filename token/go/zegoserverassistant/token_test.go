package zegoserverassistant

import (
	"fmt"
)

func Example_GenerateToken() {
	var appId uint32 = 1
	roomId := "demo"
	userId := "demo"
	serverSecret := "fa94dd0f974cf2e293728a526b028271"
	var effectiveTimeInSeconds int64 = 3600
	privilege := make(map[int]int)
	privilege[PrivilegeKeyLogin] = PrivilegeEnable
	privilege[PrivilegeKeyPublish] = PrivilegeDisable

	token, err := GenerateToken(appId, roomId, userId, privilege, serverSecret, effectiveTimeInSeconds)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(token)
}
