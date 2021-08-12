# Introduction

# Instructions

##  Importing-related

```Java
import im.zego.serverassistant.ZegoServerAssistant;
import im.zego.serverassistant.ZegoServerAssistant.TokenInfo;
```

## Room privileges description

## Error codes

```Java
enum ErrorCode {
    /**
     * 生成鉴权 token 成功
     */
    SUCCESS(0),
    /**
     * 传入 appId 参数错误
     */
    ILLEGAL_APP_ID(1),
    /**
     * 传入 userId 参数错误
     */
    ILLEGAL_USER_ID(3),
    /**
     * 传入 secret 参数错误
     */
    ILLEGAL_SECRET(5),
    /**
     * 传入 effectiveTimeInSeconds 参数错误
     */
    ILLEGAL_EFFECTIVE_TIME(6),
    /**
     * 其它未定义错误
     */
    OTHER(-1);
}
```

## generateToken parameters and return codes

```Java
/**
 * Use the following parameters to generate the token for authentication when accessing to ZEGO service
 * @param appId App ID assigned by ZEGO, the unique identifier of user.
 * @param userId User ID
 * @param secret  The secret key corresponding to AppID assigned by ZEGO. Please keep it carefully.
 * @param effectiveTimeInSeconds The validity period of token, unit: second
 * @return Returned token content. Before using the token, check whether the error field is SUCCESS. The actual token content is stored in the data field.
 */
TokenInfo generateToken04(long appId, String userId, String secret, int effectiveTimeInSeconds)
```

## demo(refer to the source directory demo/im/zego/serverassistant/demo/Test.java)

```Java
public static void main(String[] args) {
    long appId = 1L;    // Assigned by ZEGO.
    String secretKey = "12345678900987654321123456789012";  // Assigned by ZEGO.
    String userId = "demo";    // User ID, must be unique within the App ID.
    int effectiveTimeInSeconds = 300;   //  The validity period, unit: second

    ZegoServerAssistant.VERBOSE = true;    // We recommend setting to false when running it
    TokenInfo token = ZegoServerAssistant.generateToken04(appId, roomId, userId, privilege, secretKey, effectiveTimeInSeconds);
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

3. Copy the content under the src/ directory to the source directory of your project, and call the ZegoServerAssistant.generateToken04 method as described above.