cmake_minimum_required(VERSION 3.20.0)
project(staff_manager)
set(CMAKE_CXX_STANDARD 17)

# 设置可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 收集 src 目录下的所有源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LISTS)

# 添加主程序文件
list(APPEND SRC_LISTS ${PROJECT_SOURCE_DIR}/staff-manager-main.cpp)

# 创建可执行文件
add_executable(app ${SRC_LISTS})

# 指定头文件目录
target_include_directories(app PRIVATE ${PROJECT_SOURCE_DIR}/include)