#!/usr/bin/env python -u
# coding:utf-8

#
# 基础鉴权 token 生成示例
#

import sys
import os
cur_path = os.path.abspath(os.path.dirname(__file__))
root_path = os.path.split(cur_path)[0]
sys.path.append(root_path)
from src import token04

if __name__ == '__main__':

    # 请将 app_id 修改为你的 appID，appID 为 数字，从即构控制台获取
    # 举例：1234567890
    app_id = 
    
    # 请将 请将 server_secret 修改为你的 serverSecret，serverSecret 为 string，从即构控制台获取
    # 举例："fa94dd0f974cf2e293728a526b028271"
    server_secret = 

    # 请将 user_id 修改为用户的 user_id，user_id 为 string
    # 举例："user1"
    user_id = "user1"

    # token 过期时间，单位：秒
    effective_time_in_seconds = 3600

    # 额外配置信息
    payload = {
        "demoPayload": "" #生成基础鉴权 token时，payload 要设为空字符串
    }

    token_info = token04.generate_token04(app_id, user_id, server_secret, effective_time_in_seconds, json.dumps(payload))
    print([token_info.token, token_info.error_code, token_info.error_message])
