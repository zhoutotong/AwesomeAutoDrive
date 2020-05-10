#Author:       zhoutotong
cmake_minimum_required(VERSION 3.10)

set(SOURCE_FILES               #设置变量，表示所有的源文件
main.cpp
vehicle_factory.cpp
vehicle_manager.cpp
vehicle.cpp
)


include_directories(                          #相关头文件的目录

)

#添加子目录


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# target_link_libraries(${PROJECT_NAME} )

