cmake_minimum_required(VERSION 3.6)

FILE(GLOB_RECURSE SOURCES *.h* *.c*)

link_directories(${CMAKE_HOME_DIRECTORY}/build)
link_libraries(zego_server_assistant)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_HOME_DIRECTORY}/kernel/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_HOME_DIRECTORY}/common)