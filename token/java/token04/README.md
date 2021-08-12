# 简介

# 使用说明

## 导入辅助类

```Java
import im.zego.serverassistant.ZegoServerAssistant;
import im.zego.serverassistant.ZegoServerAssistant.TokenInfo;
```

## 错误码说明

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

## generateToken04 参数及返回值说明

```Java
/**
 * 根据所提供的参数列表生成用于与即构服务端通信的鉴权 token
 * @param appId Zego派发的数字ID, 各个开发者的唯一标识
 * @param userId 用户 ID
 * @param secret 由即构提供的与 appId 对应的密钥，请妥善保管，切勿外泄
 * @param effectiveTimeInSeconds token 的有效时长，单位：秒
 * @return 返回 token 内容，在使用前，请检查 error 字段是否为 SUCCESS。实际 token 内容保存在 data 字段中
 */
TokenInfo generateToken04(long appId, String userId, String secret, int effectiveTimeInSeconds)
```

## demo(参见源码目录 demo/im/zego/serverassistant/demo/Test.java)

```Java
public static void main(String[] args) {
    long appId = 1L;    // 由即构提供
    String secretKey = "12345678900987654321123456789012";  // 由即构提供
    String userId = "demo";    // 用户 ID，同一 appId 下全网唯一
    int effectiveTimeInSeconds = 300;   // 有效时间，单位：秒

    ZegoServerAssistant.VERBOSE = true;    // 正式运行时，最好置为 false
    TokenInfo token = ZegoServerAssistant.generateToken04(appId, roomId, userId, privilege, secretKey, effectiveTimeInSeconds);
    System.out.println(token);
}
```

# 接入 SDK 说明

## 源码引入方式使用说明

1. 前往 [Github 代码托管地址](https://github.com/zegoim/zego_server_assistant) 下载最新代码。

2. 若项目中已使用了 com.googlecode.json-simple 库，请忽略此步，否则根据你项目的组织方式选择如下方式之一进行引入。

### 1.如果你的项目使用 maven 进行管理，请将如下内容添加至你项目根目录下的 pom.xml 文件中
```xml
<dependency>
    <groupId>com.googlecode.json-simple</groupId>
    <artifactId>json-simple</artifactId>
    <version>1.1.1</version>
</dependency>
```

### 2. 如果你的项目是通过 classpath 管理，请将 libs/ 目录下的 json-simple-1.1.1.jar 拷贝至你项目根目录下的 libs/ 目录，并将如下内容添加至你项目根目录下的 .classpath 文件 <classpath> 节点中 
```xml
    <classpathentry kind="lib" path="libs/json-simple-1.1.1.jar"/>
```

3. 将 src/ 目录下的内容拷贝至你项目源代码根目录下，并按照上文使用说明使用 ZegoServerAssistant.generateToken04 方法。
