const {getToken} = require('../server/zegoServerAssistant');

const token =  getToken(2913569222, '127', 'choui', { 1: 1, 2: 0 }, 'b0d996aecc46ad51600ea853bb378c18', 3600);
console.log('token', token);