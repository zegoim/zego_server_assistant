# Introduction

## Room privileges description

```javascript
interface  kPrivilege {
    canLoginRoom:boolean, // The "key" in the privilege class, used to determine whether the user has the privilege to log in to a room;  // "value" : false means deny, true means allow.
    canPublishStream:boolean // The "key" in the privilege class, used to determine whether the user has the privilege to publish streams; // "value" : fmeans deny, true means allow.
} 
```

## Error codes

```javascript
enum ErrorCode
    {
        success                       = 0,  // Token for authentication obtained successfully.
        appIDInvalid                  = 1,  // App ID parameter is invalid.
        roomIDInvalid                 = 2,  // Room ID parameter is invalid.
        userIDInvalid                 = 3,  // User ID parameter is invalid.
        privilegeInvalid              = 4,  // Privilege parameter is invalid.
        secretInvalid                 = 5,  // Secret parameter is invalid.
        effectiveTimeInSecondsInvalid = 6   // effectiveTimeInSeconds parameter is invalid.
    };
```

## GenerateToken parameters description

```javascript
// Parameters
const appID: number;  // App ID assigned by ZEGO, the unique identifier of user.
const roomID: string;  //  Room ID
const userID: string;  //  User ID
const privilege: kPrivilege;  // Room privilege
const secret: string;   // The secret key for AES encryption when applying for token.
const effectiveTimeInSeconds: number;  // The validity period of token, unit: second

// The return value for success
const token: string

// The return value for failure
 interface ErrorInfo {
    errorCode: ErrorCode; // Error codes from ErrorCode
    errorMessage: string; // Detailed description of error codes
 }
 const errorInfo:  ErrorInfo 
```

## demo

```javascript
const { generateToken } = require('../server/zegoServerAssistant');
// Rtc Examples
const appID = 123456789;
const secret = 'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx';
const roomId = 'demo'; 
const userId = 'demo'; 
const effectiveTimeInSeconds = 3600; 
const privilege = {
            canLoginRoom:true,
            canPublishStream:true
}

// Build token 
const token =  generateToken(appID, roomId, userId, privilege, secret, effectiveTimeInSeconds);
 
```

##  Import the codes 

1. Go to [Github - zego_server_assistant](https://github.com/zegoim/zego_server_assistant) to download the latest codes.
2. Copy the nodejs/server directory to your project.
3. Import the code `const { getToken } = require('../server/zegoServerAssistant');`
