cmake_minimum_required(VERSION 3.6)

ZEGO_COLLECT_COMPLIE_SOURCE(${CMAKE_CURRENT_LIST_DIR} zego_complie_sources)
ZEGO_SOURCE_GROUP_BY_DIR(zego_complie_sources)

list(APPEND MODULES_SOURCES ${zego_complie_sources})
include_directories(${CMAKE_CURRENT_LIST_DIR})

