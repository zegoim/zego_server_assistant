cmake_minimum_required(VERSION 3.6)


target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/     
    ${CMAKE_CURRENT_LIST_DIR}/..   
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_HOME_DIRECTORY}/common/rapidjson
    ${CMAKE_HOME_DIRECTORY}/common/
    )

