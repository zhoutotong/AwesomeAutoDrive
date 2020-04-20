#Author:      zhoutotong
cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME main_widget)


# 开启 C++14支持
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 查找 Qt5 库支持
find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(rviz REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(roscpp REQUIRED)
find_package(jsk_rviz_plugins REQUIRED)


set(SOURCE_FILES
mainwidget.cpp
datarec.cpp
)

include_directories(                          #相关头文件的目录
./
../common_widget
${YAML_CPP_INCLUDE_DIR}
${rviz_INCLUDE_DIRS}
${roscpp_INCLUDE_DIRS}
${jsk_rviz_plugins_INCLUDE_DIRS}
)

link_directories(                             #相关库文件的目录
/usr/local/lib
)


add_library(${MODULE_NAME} ${SOURCE_FILES})

target_link_libraries(${MODULE_NAME} 
${rviz_LIBRARIES}
${YAML_CPP_LIBRARIES}
${roscpp_LIBRARIES}
utilities
common_widget Qt5::Core Qt5::Gui Qt5::Widgets)

