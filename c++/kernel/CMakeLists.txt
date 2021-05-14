cmake_minimum_required(VERSION 3.6)

# sources
include (${CMAKE_HOME_DIRECTORY}/kernel/sources.cmake) # ALL_SOURCES_SERVER_ASSISTANT

# target
# add_library(${PROJECT_NAME} STATIC ${ALL_SOURCES_SERVER_ASSISTANT})
add_library(${PROJECT_NAME} SHARED ${ALL_SOURCES_SERVER_ASSISTANT})

# inclue
include (${CMAKE_HOME_DIRECTORY}/kernel/include.cmake) 

# link
include (${CMAKE_HOME_DIRECTORY}/kernel/linkList.cmake)


# setting
include (${CMAKE_HOME_DIRECTORY}/kernel/setting.cmake)