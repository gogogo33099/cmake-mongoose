# armv7-toolchain.cmake
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR arm)

# 设置交叉编译器
SET(CMAKE_C_COMPILER arm-linux-gcc)
SET(CMAKE_CXX_COMPILER arm-linux-g++)

# 如果有 sysroot（如你有完整 rootfs）
# SET(CMAKE_SYSROOT /path/to/arm-sysroot)

# 可选：设置 include 和 lib 查找路径
# SET(CMAKE_FIND_ROOT_PATH /path/to/arm-sysroot)
# SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
