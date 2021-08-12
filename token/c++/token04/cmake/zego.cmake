cmake_minimum_required(VERSION 3.6)

# macro(ZEGO_SOURCE_GROUP_BY_DIR source_files)       
# 	set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR}/)	# where project define
# 	foreach(sgbd_file ${${source_files}})
# 		string(REGEX REPLACE ${sgbd_cur_dir} "" sgbd_fpath ${sgbd_file})
# 		string(REGEX REPLACE "[^/\\\\]+$" "" sgbd_group_name ${sgbd_fpath})
# 		if(sgbd_group_name)
# 			string(REPLACE "/"   "\\\\"  sgbd_group_name_normal ${sgbd_group_name})
# 			#message(STATUS ${sgbd_group_name_normal})
# 			source_group(${sgbd_group_name_normal} FILES ${sgbd_file})
# 		endif(sgbd_group_name)	
# 	endforeach(sgbd_file)
# endmacro(ZEGO_SOURCE_GROUP_BY_DIR)


macro (ZEGO_COLLECT_COMPLIE_SOURCE in_soruce_root_dir out_source_file_list)
    file(GLOB ${out_source_file_list}
        ${in_soruce_root_dir}/*.cpp
        ${in_soruce_root_dir}/*.c 
        ${in_soruce_root_dir}/*.cc
        ${in_soruce_root_dir}/*.hh
        ${in_soruce_root_dir}/*.hpp 
        ${in_soruce_root_dir}/*.h
        ${in_soruce_root_dir}/*.mm
        ${in_soruce_root_dir}/*.m
    )
endmacro (ZEGO_COLLECT_COMPLIE_SOURCE)

MACRO(ZEGO_LIST_SOURCE_DIR result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")

    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()

    FILE(GLOB children RELATIVE ${curdir} ${curdir}/XXXXX*)
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(REMOVE_ITEM dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()