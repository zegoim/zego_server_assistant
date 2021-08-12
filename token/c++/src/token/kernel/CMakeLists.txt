cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

include (${CMAKE_HOME_DIRECTORY}/kernel/sources.cmake)

add_library(${PROJECT_NAME} SHARED ${ALL_SOURCES_SERVER_ASSISTANT})

include (${CMAKE_HOME_DIRECTORY}/kernel/include.cmake) 

include (${CMAKE_HOME_DIRECTORY}/kernel/linkList.cmake)

include (${CMAKE_HOME_DIRECTORY}/kernel/setting.cmake)