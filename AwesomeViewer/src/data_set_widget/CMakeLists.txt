#Author:      zhoutotong
cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME data_set_widget)


# 开启 C++14支持
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 查找 pcl 库支持
find_package(PCL 1.2 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# 查找 Qt5 库支持
find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES
datasetwidget.cpp
bag2datawidget.cpp
dataviewer.cpp
pclviewer.cpp
)

include_directories(                          #相关头文件的目录
./
)

link_directories(                             #相关库文件的目录
/usr/local/lib
)


add_library(${MODULE_NAME} ${SOURCE_FILES})

target_link_libraries(${MODULE_NAME} Qt5::Core Qt5::Gui Qt5::Widgets ${PCL_LIBRARIES})

