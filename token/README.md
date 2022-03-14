# 简介
本代码库是zego服务token生成工具库。


# 使用说明
* ZIM业务token鉴权请使用04版本token(ZIM不支持payload参数)
* RTC业务现在提供04版本Token鉴权  

  对于要在App终端生成Token(不推荐使用)
  
     oc：复制 \oc\rapidjson \oc\token04 加入到你的工程项目，调用GenerateToken04接口即可，详情参照sample.mm, 更高级别权限控制参照sample-for-rtcroom.mm  
	 
	 c++: 复制 \token\c++\token04 中的源文件，和头文件加入到你的工程，调用GenerateToken04接口即可，详情参照main.cc 
	 
	 java: 复制 \java\token04\src 中的源文件，加入到你的工程，调用generateToken04 接口即可 详情参照Token04Sample.java  
	 
	 注意：
	     1、终端生成Token c++和Java 与服务端代码是通用的,直接复制文件到你的工程即可
		 
		 2、生成Token 库中有使用rapidjson库，用户也可用自己的json库代替
		 
         3、payload 为04 Token版本新增参数(默认为空，或者不传递即可)为Json 字符串，用于更高级别的权限控制，如有需要此功能可联系Zego技术支持
		 
		    基本Json格式如下:    
                    {
                       "room_id": "roomid", //房间id，限制用户只能登录特定房间,空表示不限制  
                       "privilege": {  
                                      "1": 1,   //是否允许登录房间 1 允许 0关闭    
                                      "2": 1   //是否允许推流    1 允许 0关闭   
                                    },  
                       "stream_id_list": ["s123"] //流id数组:限制用户只能推指定流,stream_id_list为空，则不限制  
                    }
 
