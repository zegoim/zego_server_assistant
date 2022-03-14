const { generateToken04 } = require('../server/zegoServerAssistant');

const appID = 1; // type: number
const secret = 'fa94dd0f974cf2e293728a526b028271';// type: 32 byte length string
const userId = 'demo';// type: string
const effectiveTimeInSeconds = 3600; //type: number; unit: s
const payload = ''; // extend string
// Build token 
const token =  generateToken04(appID, userId, secret, effectiveTimeInSeconds, payload);
console.log('token:',token);