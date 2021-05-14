if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DWIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DUNICODE -D_UNICODE -D_SCL_SECURE_NO_WARNINGS )
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DNOMINMAX -DWIN32_LEAN_AND_MEAN)
else (LINUX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DLINUX)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE 
        -D V_LOG # xplatform
        -D ZEGO_EXPORTS # dll 到处接口符号
        # -DRAPIDJSON_HAS_STDSTRING # rapid json
        # -D_WINSOCKAPI_
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -DZEGO_SDK_VER="${ZEGO_SDK_VER}")

if(NOT WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Bsymbolic -Xlinker -z -Xlinker defs -Wl,--exclude-libs=ALL")
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})