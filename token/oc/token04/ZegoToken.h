//
//  ZegoToken.h
//  MakeToken
//
//  Created by zavierzhang on 2022/3/5.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, ZegoErrorCode) {
    success = 0,  // 获取鉴权 token 成功
    appIDInvalid = 1,  // 调用方法时传入 appID 参数错误
    userIDInvalid = 3,  // 调用方法时传入 userID 参数错误
    secretInvalid = 5,  // 调用方法时传入 secret 参数错误
    effectiveTimeInSecondsInvalid = 6   // 调用方法时传入 effectiveTimeInSeconds 参数错误
};


@interface ErrorInfo : NSObject

@property (nonatomic, assign) ZegoErrorCode errorCode;
@property (nonatomic, copy) NSString *errorMessage;

@end


@interface ZegoToken04Result : NSObject

@property (nonatomic, copy) NSString *token;
@property (nonatomic, strong) ErrorInfo *errorInfo;

@end

@interface ZegoToken : NSObject

+ (ZegoToken04Result*) GenerateToken04:(unsigned int)appid userID:(NSString*)userID  secret:(NSString*)secret effectiveTimeInSeconds:(long long)effectiveTimeInSeconds payload:(NSString*)payload;

@end

NS_ASSUME_NONNULL_END

