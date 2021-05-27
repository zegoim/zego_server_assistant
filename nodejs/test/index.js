const { generateToken } = require('../server/zegoServerAssistant');

const appID = '<Your appID>'; // type: number
const secret = '<Your app certificate>';// type: 32 byte length string
const roomId = '<The roomId this token is generated for>';// type: string
const userId = '<Your userId ID>';// type: string
const effectiveTimeInSeconds = '<Your token effectiveTime>'; //type: number; unit: s
const privilege = {
            1: 1,// loginRoom: 1 pass , 0 not pass
            2: 1 //  publishStream: 1 pass , 0 not pass
}
// Build token 
const token =  generateToken(appID, roomId, userId, privilege, secret, effectiveTimeInSeconds);
console.log('token:',token);