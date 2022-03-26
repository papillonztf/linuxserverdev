cmake_minimum_required(VERSION 3.0.0)
project(mytest VERSION 0.1.0)

#gcc/g++编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -Wall -O0 -Wno-unused-variable -pthread")

#主程序(测试)源文件
set(main
#./positiveTest1.cpp
./negativeTest1.cpp
#./negativeTest2.cpp
)

#递归指定目录的所有源文件 
aux_source_directory(./source srcfiles_list) #相对与PROJECT_SOURCE_DIR(=最上层CMakeLists.txt所在目录)
#message("PROJECT_SOURCE _DIR = ${PROJECT_SOURCE_DIR})

#自定义头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

#生成可执行文件main 
add_executable(main  ${main}  ${srcfiles_list})

#可执行文件存放位置
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR})