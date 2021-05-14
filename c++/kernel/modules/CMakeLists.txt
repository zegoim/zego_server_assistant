cmake_minimum_required(VERSION 3.6)

include_directories(${CMAKE_CURRENT_LIST_DIR})

file(GLOB folders RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/*)
foreach(folder ${folders})
    if(IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${folder})
        include (${CMAKE_CURRENT_LIST_DIR}/${folder}/CMakeLists.txt)
    endif()
endforeach()

ZEGO_COLLECT_COMPLIE_SOURCE(${CMAKE_CURRENT_LIST_DIR} zego_complie_sources)
# ZEGO_SOURCE_GROUP_BY_DIR(zego_complie_sources)
list(APPEND MODULES_SOURCES ${zego_complie_sources})