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
    NSString * serverKey= @"your_server_key";
    NSString * userID= @"demo_id_name";
    long long appid= 1;
    long long expireTime = 36000;
    
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
