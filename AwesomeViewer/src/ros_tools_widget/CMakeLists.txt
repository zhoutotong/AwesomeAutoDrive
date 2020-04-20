#Author:      zhoutotong
cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES               #设置变量，表示所有的源文件
main.cpp
mainwindow.cpp
)


include_directories(                          #相关头文件的目录
${PROJET_SOURCE_DIR}/src
/home/tong/Qt5.14.1/5.14.1/gcc_64/include
/home/tong/Qt5.14.1/5.14.1/gcc_64/include/QtWidgets
)

link_directories(                             #相关库文件的目录
/usr/local/lib
/home/tong/Qt5.14.1/5.14.1/gcc_64/lib
)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)

