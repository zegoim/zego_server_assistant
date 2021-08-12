cmake_minimum_required(VERSION 3.6)

project(token_generator_sln)

# cmake include
include (${CMAKE_HOME_DIRECTORY}/cmake/zego.cmake)

# main project
project(token_generator)
message(${PROJECT_NAME})
include(${CMAKE_HOME_DIRECTORY}/kernel/CMakeLists.txt)

option(BUILD_TEST "" ON)
if(BUILD_TEST)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/sample/token)
endif()