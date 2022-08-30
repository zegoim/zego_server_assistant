#!/usr/bin/env python -u
# coding:utf-8

#
# 权限认证 token 生成示例，使用前需联系即构技术支持开通功能
#

import json
import os
import sys
cur_path = os.path.abspath(os.path.dirname(__file__))
root_path = os.path.split(cur_path)[0]
sys.path.append(root_path)
from src import token04

if __name__ == '__main__':

    # 请将 app_id 修改为你的 appId，appId 为 数字，从即构控制台获取
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

    # 权限认证 token 的权限控制信息通过 payload 控制
    payload = {
        "room_id": "room1", # 房间 ID
        "privilege": {
            1 : 1, # key为 1 代表 房间权限，value 为 1 代表允许，所以这里代表允许房间登录；如果 value 为 0，代表不允许
            2 : 1  # key为 2 代表 推流权限，value 为 1 代表允许，所以这里代表允许推流；如果 value 为 0，代表不允许
        }, 
        "stream_id_list": None # 传 None 代表所有的流都可以推流。如果传入一个 streamID 列表，则只有列表内的 streamID 才能推流
    }

    ## 3600 为 token 过期时间，单位：秒
    token_info = token04.generate_token04(app_id=app_id, user_id=user_id, secret=server_secret,
                                          effective_time_in_seconds=effective_time_in_seconds, payload=json.dumps(payload))
    print([token_info.token, token_info.error_code, token_info.error_message])
