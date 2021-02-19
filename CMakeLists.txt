cmake_minimum_required(VERSION 3.19)
project(ellisya_vm)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

set(CMAKE_CXX_STANDARD 20)

add_executable(ellisya_vm ellisya.cpp)
add_executable(assembler assembler.cpp)