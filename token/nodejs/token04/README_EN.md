# Introduction

## Error codes

```javascript
enum ErrorCode
    {
        success                       = 0,  // Token for authentication obtained successfully.
        appIDInvalid                  = 1,  // App ID parameter is invalid.
        userIDInvalid                 = 3,  // User ID parameter is invalid.
        secretInvalid                 = 5,  // Secret parameter is invalid.
        effectiveTimeInSecondsInvalid = 6   // effectiveTimeInSeconds parameter is invalid.
    };
```

## GenerateToken04 parameters description

```javascript
// Parameters
const appID: number;  // App ID assigned by ZEGO, the unique identifier of user.
const userID: string;  //  User ID
const secret: string;   // The secret key for AES encryption when applying for token.
const effectiveTimeInSeconds: number;  // The validity period of token, unit: second
const payload: string; // custom data


// The return value for success
const token: string

// The return value for failure
 interface ErrorInfo {
    errorCode: ErrorCode; // Error codes from ErrorCode
    errorMessage: string; // Detailed description of error codes
 }
 const errorInfo:  ErrorInfo 
```

## general token generate demo

- The general token is used for simple authorization of service interfaces, and the payload field can be empty

```javascript
const { generateToken04 } = require('../server/zegoServerAssistant');
// Rtc Examples
const appID = 123456789;
const secret = 'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx';
const userId = 'demo'; 
const effectiveTimeInSeconds = 3600; 
const payload = '';

// Build token 
const token =  generateToken04(appID, userId, secret, effectiveTimeInSeconds, payload);
 
```

## strict token generate demo

- The strict token is used in scenarios where strong authentication is required for login-room/push-stream/pull-stream permissions. The payload field should be generated according to the specifications.

```javascript
const { generateToken04 } = require('../server/zegoServerAssistant');

const appID = 1; // type: number
const secret = 'fa94dd0f974cf2e293728a526b028271';// type: 32 byte length string
const userId = 'demo';// type: string
const effectiveTimeInSeconds = 3600; //type: number; unit: s
const payloadObject = {
    room_id: 'demo',
    privilege: {
        1: 1,   // loginRoom: 1 pass , 0 not pass
        2: 0    // publishStream: 1 pass , 0 not pass
    },
    stream_id_list: null
}; // 
const payload = JSON.stringify(payloadObject);
// Build token 
const token =  generateToken04(appID, userId, secret, effectiveTimeInSeconds, payload);

```


## Import the codes

1. Go to [Github - zego_server_assistant](https://github.com/zegoim/zego_server_assistant) to download the latest codes.
2. Copy the nodejs/token04/server directory to your project.
3. Import the code `const { getToken } = require('../server/zegoServerAssistant');`
