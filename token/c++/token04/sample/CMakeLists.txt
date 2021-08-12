cmake_minimum_required(VERSION 3.6)

# get all dir
ZEGO_LIST_SOURCE_DIR(mysubdirs ${CMAKE_CURRENT_LIST_DIR})
list(REMOVE_ITEM mysubdirs macro)

# add all subdirs
FOREACH(subdir ${mysubdirs})
    project(${subdir})
    #add_subdirectory(${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER sample)

    if (WIN32)
        target_compile_definitions(${PROJECT_NAME} PRIVATE -D_CRT_SECURE_NO_WARNINGS)
        target_compile_definitions(${PROJECT_NAME} PRIVATE -D_WIN32_WINNT=0x0a00)
    endif()

ENDFOREACH()