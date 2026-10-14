cmake_minimum_required(VERSION 3.15)
project(mipt_cpp_hw1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
  add_compile_options(/utf-8 /W4)
endif()

add_executable(task1 task1/main.cpp)
add_executable(task2 task2/main.cpp)
add_executable(task3 task3/main.cpp)
add_executable(task4 task4/main.cpp)