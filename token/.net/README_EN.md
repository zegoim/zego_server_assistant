# Introduction

# Instructions

## Import the header file, namespace

```c#
using ZegoServerAssistant;
using Newtonsoft.Json;
```

## Room privileges description

```c#
public enum kPrivilege
{
    kPrivilegeLogin = 1,  // The "key" value of the map in the privilege class, used to determine whether the user has the privilege to log in to a room;
                          // "value" : 0 means deny, 1 means allow.
    kPrivilegePublish = 2  // The "key" value of the map in the privilege class, used to determine whether the user has the privilege to publish streams;
                           // "value" : 0 means deny, 1 means allow.
};
```

## Error codes description

```c#
public enum ErrorCode
{
	success = 0,  				// Token for authentication obtained successfully.
	appIDInvalid = 1,   				// App ID parameter is invalid.
	roomIDInvalid = 2,  				// Room ID parameter is invalid.
	userIDInvalid = 3,  				// User ID parameter is invalid.
	privilegeInvalid = 4,  				// Privilege parameter is invalid.
	secretInvalid = 5,  				// Secret parameter is invalid.
	effectiveTimeInSecondsInvalid = 6  	// effectiveTimeInSeconds parameter is invalid.
};
```

## GenerateToken parameters and return codes

```c#
/**
 * Use the following parameters to generate the token for authentication when accessing to ZEGO service
 * @param appId App ID assigned by ZEGO, the unique identifier of user.
 * @param roomId Room ID
 * @param userId User ID
 * @param privilege Room privilege
 * @param secret  The secret key corresponding to AppID assigned by ZEGO. Please keep it carefully.
 * @param effectiveTimeInSeconds The validity period of token, unit: second
 * @return Returned token content. Before using the token, check whether the errorInfo field is SUCCESS. The actual token content is stored in the token field.
 */
public static GenerateTokenResult GenerateToken(uint appID, string roomID, string userID, Dictionary<int, int> privilege, string secret, long effectiveTimeInSeconds)
```

## demo

```c#
public Form1()
{
		InitializeComponent();

		Dictionary<int, int> privilege = new Dictionary<int, int>();
		privilege[1] = 1;
		privilege[2] = 1;

		ZegoServerAssistant.GenerateTokenResult result = ZegoServerAssistant.ServerAssistant.GenerateToken(1, "111", "222", privilege, "12345678900987654321123456789012", 3600);
}
```

# Instructions of integrating the SDK

## Import the codes 

1. Go to [Github- zego_server-assistant](https://github.com/zegoim/zego_server_assistant) to download the latest codes.
2. Open the ZegoServerAssistant.sln solution in Visual Studio and exported it as  ZegoServerAssistant.dll, and import this .dll file into your project, or directly integrate the  GenerateToken.cs codes into your project.
3. Call the GenerateToken method as described above.
