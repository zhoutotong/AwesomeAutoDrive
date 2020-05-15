#Author:       zhoutotong
cmake_minimum_required(VERSION 3.10)


find_package(yaml-cpp REQUIRED)

set(SOURCE_FILES               #设置变量，表示所有的源文件
base_factory.cpp
base_device.cpp
awesome_vehicle.cpp
vehicle_factory.cpp
vehicle_manager.cpp
vehicle.cpp
main.cpp
)


include_directories(           #相关头文件的目录
./
utilities
${YAML_CPP_INCLUDE_DIR}
)

#添加子目录
add_subdirectory(utilities)
add_subdirectory(sensors)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} 
sensors
utilities
${YAML_CPP_LIBRARIES}
)


