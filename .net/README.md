### Generate
```c#
// Rtc Examples
using ZegoServerAssistant;
using Newtonsoft.Json;

uint appId = '<Your app ID>'; // type: number
string roomId = '<The channel this token is generated for>';// type: string
string userId = '<Your app ID>';// type: string
Dictionary<int, int> privilege = new Dictionary<int, int>();
//privilege[1] = 1;
//privilege[2] = 1;
string secret = '<Your app certificate>';// type: 32 byte length string
long effectiveTimeInSeconds = '<Your token effectiveTime>'; //type: number; unit: s

// Build token 
ZegoServerAssistant.GenerateTokenResult result = ZegoServerAssistant.ServerAssistant.GenerateToken(appId, roomId, userId, privilege, secret, effectiveTimeInSeconds);

```