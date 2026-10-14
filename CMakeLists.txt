cmake_minimum_required(VERSION 3.15)
project(mipt_cpp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
  add_compile_options(/utf-8 /W4)
endif()

add_subdirectory(hw1)