# author:>---zhoutotong

cmake_minimum_required(VERSION 3.10)    #cmake 最低版本要求，低于 3.10 构建过程会被终止。

PROJECT(AwesomeViewer)                 #定义工程名称

# 打开C++14支持
set(CMAKE_BUILE_TYPE DEBUG)            
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 指定编译选项
set(CMAKE_C_FLAGS_DEBUG "-g -Wall")

# 子目录
add_subdirectory(src)