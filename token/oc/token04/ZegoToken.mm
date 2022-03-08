//
//  ZegoToken.m
//  MakeToken
//
//  Created by zavierzhang on 2022/3/5.
//

#import "ZegoToken.h"
#include "ZegoServerAssistant.h"

#include "json_tools.hpp"

@implementation ErrorInfo

@end

@implementation ZegoToken04Result


@end


@implementation ZegoToken


+ (ZegoToken04Result*) GenerateToken04:(unsigned int)appid userID:(NSString*)userID  secret:(NSString*)secret effectiveTimeInSeconds:(long long)effectiveTimeInSeconds payload:(NSString*)payload;
{
    ErrorInfo* errorInfo =[[ErrorInfo alloc] init];
    ZegoToken04Result* result = [[ZegoToken04Result alloc] init];
    result.errorInfo = errorInfo;
    
    if(appid == 0)
    {
        result.errorInfo.errorCode = ZegoErrorCode::appIDInvalid;
        return result;
    }
    
    if(!userID.length)
    {
        result.errorInfo.errorCode = ZegoErrorCode::userIDInvalid;
        return result;
    }
    
    if(!secret.length)
    {
        result.errorInfo.errorCode = ZegoErrorCode::secretInvalid;
        return result;
    }
    
    NSString* playloadJson = @"";
    if(payload.length)
    {
        playloadJson = payload;
    }
    
    ZEGO::SERVER_ASSISTANT::ZegoToken04Result tokenResult = ZEGO::SERVER_ASSISTANT::ZegoServerAssistant::GenerateToken04(appid,userID.UTF8String,secret.UTF8String,effectiveTimeInSeconds,playloadJson.UTF8String);
    
    switch(tokenResult.errorInfo.errorCode)
    {
        case ZEGO::SERVER_ASSISTANT::ErrorCode::success:
            result.errorInfo.errorCode = ZegoErrorCode::success;
            break;
        case ZEGO::SERVER_ASSISTANT::ErrorCode::appIDInvalid:
            result.errorInfo.errorCode = ZegoErrorCode::appIDInvalid;
            break;
        case ZEGO::SERVER_ASSISTANT::ErrorCode::userIDInvalid:
            result.errorInfo.errorCode = ZegoErrorCode::userIDInvalid;
            break;
        case ZEGO::SERVER_ASSISTANT::ErrorCode::secretInvalid:
            result.errorInfo.errorCode = ZegoErrorCode::secretInvalid;
            break;
        case ZEGO::SERVER_ASSISTANT::ErrorCode::effectiveTimeInSecondsInvalid:
            result.errorInfo.errorCode = ZegoErrorCode::effectiveTimeInSecondsInvalid;
            break;
    }
    
    result.errorInfo.errorMessage = [NSString stringWithUTF8String:tokenResult.errorInfo.errorMessage.c_str()];
    result.token = [NSString stringWithUTF8String:tokenResult.token.c_str()];
    
    return  result;
}

@end
