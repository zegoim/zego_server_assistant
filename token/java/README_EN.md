# Introduction

# Instructions

##  Importing-related

```Java
import im.zego.serverassistant.ZegoServerAssistant;
import im.zego.serverassistant.ZegoServerAssistant.Privileges;
import im.zego.serverassistant.ZegoServerAssistant.TokenInfo;
```

## Room privileges description

```Java
class Privileges {
    /** whether the user has the privilege to log in to a room, no privilege is by default.*/
    boolean canLoginRoom;

    /** whether the user has the privilege to publish streams, no privilege is by default. */
    boolean canPublishStream;
}
```

## Error codes

```Java
enum ErrorCode {
    /** token for authentication generated successfully */
    SUCCESS,
    /**  appId parameter is incorrect */
    ILLEGAL_APP_ID,
    /**  roomId parameter is incorrect */
    ILLEGAL_ROOM_ID,
    /**  userId parameter is incorrect */
    ILLEGAL_USER_ID,
    /**  privilege parameter is incorrect */
    ILLEGAL_PRIVILEGE,
    /**  secret parameter is incorrect */
    ILLEGAL_SECRET,
    /** effectiveTimeInSeconds parameter is incorrect */
    ILLEGAL_EFFECTIVE_TIME,
    /** other errors */
    OTHER;
}
```

## generateToken parameters and return codes

```Java
/**
 * Use the following parameters to generate the token for authentication when accessing to ZEGO service
 * @param appId App ID assigned by ZEGO, the unique identifier of user.
 * @param roomId Room ID
 * @param userId User ID
 * @param privilege Room privilege
 * @param secret  The secret key corresponding to AppID assigned by ZEGO. Please keep it carefully.
 * @param effectiveTimeInSeconds The validity period of token, unit: second
 * @return Returned token content. Before using the token, check whether the error field is SUCCESS. The actual token content is stored in the data field.
 */
TokenInfo generateToken(long appId, String roomId, String userId, Privileges privilege, String secret, int effectiveTimeInSeconds)
```

## demo(refer to the source directory demo/im/zego/serverassistant/demo/Test.java)

```Java
public static void main(String[] args) {
    long appId = 1L;    // Assigned by ZEGO.
    String secretKey = "12345678900987654321123456789012";  // Assigned by ZEGO.
    String roomId = "demo";  // Room ID, must be unique within the App ID.
    String userId = "demo";    // User ID, must be unique within the App ID.
    int effectiveTimeInSeconds = 300;   //  The validity period, unit: second

    Privileges privilege = new Privileges();
    privilege.canLoginRoom = true;
    privilege.canPublishStream = true;
    ZegoServerAssistant.VERBOSE = true;    // We recommend setting to false when running it
    TokenInfo token = ZegoServerAssistant.generateToken(appId, roomId, userId, privilege, secretKey, effectiveTimeInSeconds);
    System.out.println(token);
}
```

# Instructions of integrating the SDK

## Import the codes and related methods

1. Go to [Github- zego_server-assistant](https://github.com/zegoim/zego_server_assistant) to download the latest codes.

2. Skip this step if you have used the com.googlecode.json-simple library. If not, import the codes by one of the following methods: 

### 1. If you are managing your project using maven, add the following content to the pom.xml file under the root directory of your project
```xml
<dependency>
    <groupId>com.googlecode.json-simple</groupId>
    <artifactId>json-simple</artifactId>
    <version>1.1.1</version>
</dependency>
```

### 2. If you are managing your project using classpath, copy the json-simple-1.1.1.jar under the libs/ directory to the libs/ directory under the root directory of your project, and copy the following content to the <classpath> node in the  .classpath  file. 
```xml
    <classpathentry kind="lib" path="libs/json-simple-1.1.1.jar"/>
```

3. Copy the content under the src/ directory to the source directory of your project, and call the ZegoServerAssistant.generateToken method as described above.