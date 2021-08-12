#!/usr/bin/env python -u
# coding:utf-8
import sys
import os
cur_path = os.path.abspath(os.path.dirname(__file__))
root_path = os.path.split(cur_path)[0]
sys.path.append(root_path)
from src import zego_server_assistant

if __name__ == '__main__':
    token_info = zego_server_assistant.generate_token(1, "demo", "demo", {
          1 : 1, 2 : 1}, "fa94dd0f974cf2e293728a526b028271", 3600)
    print([token_info.token, token_info.error_code, token_info.error_message])