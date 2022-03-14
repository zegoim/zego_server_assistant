#!/usr/bin/env python -u
# coding:utf-8
import json
import os
import sys
cur_path = os.path.abspath(os.path.dirname(__file__))
root_path = os.path.split(cur_path)[0]
sys.path.append(root_path)
from src import token04

if __name__ == '__main__':
    payload = {
        "room_id": "demo",
        "privilege": {1 : 1, 2 : 1},
        "stream_id_list": None
    }
    token_info = token04.generate_token04(app_id=1, user_id="demo", secret="fa94dd0f974cf2e293728a526b028271",
                                          effective_time_in_seconds=3600, payload=json.dumps(payload))
    print([token_info.token, token_info.error_code, token_info.error_message])
