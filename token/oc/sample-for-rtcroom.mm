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
}

- (IBAction)OnMakeToken:(id)sender
{
    NSString * serverKey= @"your_server_key;
    NSString * userID= @"demo_id_name";
    long long appid= 1;
    long long expireTime = 36000;
    
	
	//playload 为更高级别的权限控制，有需要可以咨询技术支持，后台配置开通后，可使用此方法生成Token
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("room_id","",allocator);  //填入房间id,不为空，则指定房间可以登录
    
	int loginRoomRole = 1;
	int publishRole = 1;
    rapidjson::Value privilege(rapidjson::kObjectType);
    privilege.AddMember("1",loginRoomRole,allocator);  // 生成的Token 包含登录房间权限
    privilege.AddMember("2",publishRole,allocator);  // 生成的Token 包含推流权限
    document.AddMember("privilege",privilege,allocator);
    
    rapidjson::Value streamList(rapidjson::kArrayType);
    document.AddMember("stream_id_list",streamList,allocator); //填入推流id,不为空，则只能推指定流
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    std::string payloadJson = buffer.GetString();
    
    NSString* payload = [NSString stringWithUTF8String:payloadJson.c_str()];
    
    ZegoToken04Result* tokenResult = [ZegoToken GenerateToken04:appid userID:userID secret:serverKey effectiveTimeInSeconds:expireTime payload:payload];
    
    if(tokenResult.errorInfo.errorCode == 0)
    {
         //success
        return;
    }
    else
    {
         //fail
    }
    
    
    return;
    
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
   
    
}


@end
