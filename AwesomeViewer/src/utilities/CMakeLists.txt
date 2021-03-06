#Author:      zhoutotong
cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME utilities)


# 开启 C++14支持
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 查找 Qt5 库支持
find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(roscpp REQUIRED)

find_package(yaml-cpp REQUIRED)


set(SOURCE_FILES
cfgfilehelper.cpp
rostools.cpp
execctl.cpp
utilities.cpp
datavisualization.cpp
)

include_directories(                          #相关头文件的目录
./
${YAML_CPP_INCLUDE_DIR}
${roscpp_INCLUDE_DIRS}
${CMAKE_INCLUDE_PATH}
)

link_directories(                             #相关库文件的目录
/usr/local/lib
${CMAKE_LIBRARY_PATH}
)


add_library(${MODULE_NAME} ${SOURCE_FILES})

target_link_libraries(${MODULE_NAME} Qt5::Core Qt5::Gui Qt5::Widgets
${roscpp_LIBRARIES}
${YAML_CPP_LIBRARIES}
)

