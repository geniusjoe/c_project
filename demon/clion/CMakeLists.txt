# cmake_minimum_required(VERSION <specify CMake version here>)
project(clion)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,256000")

add_executable(clion main.cpp)