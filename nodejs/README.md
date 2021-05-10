# How to use
## Install

 copy nodejs/server/zegoServerAssistant.js  to your project

## Import
```javascript
const {getToken} = require('../server/zegoServerAssistant');
```
### Generate
```javascript
// Rtc Examples
const appId = '<Your app ID>'; // type: number
const secret = '<Your app certificate>';// type: 32 byte length string
const roomId = '<The channel this token is generated for>';// type: string
const userId = '<Your app ID>';// type: string
const effectiveTimeInSeconds = '<Your token effectiveTime>'; //type: number; unit: s
const privilege = {
            1: 1,// loginRoom: 1 pass , 0 not pass
            2: 1 //  publishStream: 1 pass , 0 not pass
}

// Build token 
const token =  getToken(appID, roomId, userId, privilege, secret, effectiveTimeInSeconds);
```
