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

//
//基础鉴权token生成示例代码
//

- (IBAction)OnMakeToken:(id)sender
{
    NSString * serverKey= @"your_server_key";
    NSString * userID= @"demo_id_name";
    long long appid= 1;
    // token 过期时间，单位：秒
    long long expireTime = 36000;
    
    // 生成基础鉴权token时，最后一个参数填nil即可
    ZegoToken04Result* tokenResult = [ZegoToken GenerateToken04:appid userID:userID secret:serverKey effectiveTimeInSeconds:expireTime payload:nil];
    
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
