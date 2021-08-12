#!/usr/bin/env python -u
# coding:utf-8
import sys
import os
cur_path = os.path.abspath(os.path.dirname(__file__))
root_path = os.path.split(cur_path)[0]
sys.path.append(root_path)
from src import token04

if __name__ == '__main__':
    token_info = token04.generate_token04(1, "demo", "12345678900987654321123456789012", 3600)
    print([token_info.token, token_info.error_code, token_info.error_message])