#Author:       zhoutotong
cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(roscpp REQUIRED)

set(SOURCE_FILES               #设置变量，表示所有的源文件
main.cpp
mainwindow.cpp
)


include_directories(                          #相关头文件的目录
./
./common_widget
./data_set_widget
./main_widget
./detail_widget
${roscpp_INCLUDE_DIRS}
${CMAKE_INCLUDE_PATH}
)

link_directories(                             #相关库文件的目录
/usr/local/lib
)

#添加子目录
add_subdirectory(common_widget)
add_subdirectory(main_widget)
add_subdirectory(config_widget)
add_subdirectory(data_set_widget)
add_subdirectory(utilities)
add_subdirectory(detail_widget)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} 
${roscpp_LIBRARIES}
main_widget
data_set_widget 
common_widget
config_widget
detail_widget
Qt5::Core 
Qt5::Gui 
Qt5::Widgets)

