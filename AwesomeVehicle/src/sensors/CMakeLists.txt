#Author:      zhoutotong
cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME sensors)


# 开启 C++14支持
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES
sensor.cpp
camera.cpp
)

include_directories(                          #相关头文件的目录
./
)


add_library(${MODULE_NAME} ${SOURCE_FILES})

target_link_libraries(${MODULE_NAME}
utilities
)

