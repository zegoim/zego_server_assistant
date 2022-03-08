//
//  ViewController.m
//  MakeToken
//
//  Created by zavierzhang on 2022/3/3.
//

#import "ViewController.h"
#include "token04/ZegoToken.h"
#include "token04/json_tools.hpp"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    self.ServerSecretKey.stringValue = @"d0aed694dc1d6e3cd1b3430df9decb99";
    self.AppIDField.stringValue = @"1739272706";
    self.UserIDField.stringValue = @"token_mac_test";
    self.ExpireTimeField.stringValue = @"360000";
}

- (IBAction)OnMakeToken:(id)sender
{
    NSString * serverKey= self.ServerSecretKey.stringValue;
    NSString * userID= self.UserIDField.stringValue;
    long long appid= self.AppIDField.stringValue.longLongValue;
    long long expireTime = self.ExpireTimeField.stringValue.longLongValue;
    
    NSString* payload = nil;
	/*
	playload 为更高级别的权限控制，有需要可以咨询技术支持
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("room_id","",allocator);
    
    rapidjson::Value privilege(rapidjson::kObjectType);
    privilege.AddMember("1",(int)self.LoginRoomRole.state,allocator);
    privilege.AddMember("2",(int)self.PublishRole.state,allocator);
    document.AddMember("privilege",privilege,allocator);
    
    rapidjson::Value streamList(rapidjson::kArrayType);
    document.AddMember("stream_id_list",streamList,allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    std::string payloadJson = buffer.GetString();
    
    NSString* payload = [NSString stringWithUTF8String:payloadJson.c_str()];
	*/
    
    ZegoToken04Result* tokenResult = [ZegoToken GenerateToken04:appid userID:userID secret:serverKey effectiveTimeInSeconds:expireTime payload:payload];
    
    if(tokenResult.errorInfo.errorCode == 0)
    {
        self.TokenField.stringValue = tokenResult.token;
        return;
    }
    else
    {
        self.TokenField.stringValue = @"生成Token 失败";
    }
    
    
    return;
    
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
   
    
}


@end
