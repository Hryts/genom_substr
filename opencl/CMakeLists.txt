cmake_minimum_required(VERSION 3.14)
project(opencl)

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -framework OpenCL")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lOpenCL")
endif ()

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCL)

add_executable(opencl main.cpp rw_utils.cpp rw_utils.h opencl_utils.cpp opencl_utils.h)

target_link_libraries(opencl ${OpenCL_Libraries})