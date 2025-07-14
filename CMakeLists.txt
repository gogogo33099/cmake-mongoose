cmake_minimum_required(VERSION 3.10)
project(webui-plain VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

# 自动收集 src 目录下的所有源文件
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c)
add_executable(iotng ${SOURCES})
target_include_directories(iotng PRIVATE src)
#target_compile_definitions(prog PRIVATE MG_TLS=MG_TLS_BUILTIN)
#target_compile_definitions(iotng PRIVATE MG_ENABLE_CUSTOM_LOG)

# 安装到 INSTALL_PREFIX 根目录
install(TARGETS iotng DESTINATION .)
# 安装 Webroot 目录
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/web_root/ DESTINATION web_root)

# 安装打包
set(CPACK_PACKAGE_NAME "iotng")               # 包名
set(CPACK_PACKAGE_VERSION "1.0.0")            # 版本
set(CPACK_GENERATOR "TGZ")                    # 指定打包为 tar.gz
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${IOTNG_TARGET}-${CPACK_PACKAGE_VERSION}")
include(CPack)
