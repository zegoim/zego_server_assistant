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
const { generateToken04 } = require('../server/zegoServerAssistant');
// Rtc Examples
const appID = 123456789;
const secret = 'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx';
const userId = 'demo'; 
const effectiveTimeInSeconds = 3600; 

// Build token 
const token =  generateToken04(appID, userId, secret, effectiveTimeInSeconds);
 
```

##  Import the codes 

1. Go to [Github - zego_server_assistant](https://github.com/zegoim/zego_server_assistant) to download the latest codes.
2. Copy the nodejs/server directory to your project.
3. Import the code `const { getToken } = require('../server/zegoServerAssistant');`
