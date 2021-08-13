const { generateToken04 } = require('../server/zegoServerAssistant');

const appID = '<Your appID>'; // type: number
const secret = '<Your app certificate>';// type: 32 byte length string
const userId = '<Your userId ID>';// type: string
const effectiveTimeInSeconds = '<Your token effectiveTime>'; //type: number; unit: s
// Build token 
const token =  generateToken04(appID, userId, secret, effectiveTimeInSeconds);
console.log('token:',token);