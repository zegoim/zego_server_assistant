cmake_minimum_required(VERSION 3.6)

FILE(GLOB_RECURSE SOURCES *.h* *.c*)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_HOME_DIRECTORY}/build)

set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_INTERFACE_MULTIPLICITY 3)
target_link_libraries(${PROJECT_NAME} PRIVATE zego_server_assistant) 

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_HOME_DIRECTORY}/kernel/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_HOME_DIRECTORY}/common)