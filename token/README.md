# 简介
本代码库是zego服务token生成工具库。


# 使用说明
* ZIM业务token鉴权请使用04版本token
* RTC业务现在提供04版本Token鉴权
  对于要在App终端生成Token(不推荐使用)
     oc：复制 \oc\rapidjson \oc\token04 加入到你的工程项目，调用GenerateToken04接口即可，详情参照sample.mm
	 c++: 复制 \token\c++\token04 中的源文件，和头文件加入到你的工程，调用GenerateToken04接口即可，详情参照main.cc
	 java: 复制 \java\token04\src 中的源文件，加入到你的工程，调用generateToken04 接口即可 详情参照Token04Sample.java
	 
	 注意：
	     1、终端生成Token c++和Jva 与服务端代码是通用的
		 2、生成Token 库中有使用rapidjson库，用户也可用自己的json库代替
 
