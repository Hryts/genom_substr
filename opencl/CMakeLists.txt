cmake_minimum_required(VERSION 3.14)
project(opencl)

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -framework OpenCL")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lOpenCL")
endif ()

if (WIN32)
    find_library( LibArchive NAMES libarchive.dll )
elseif(APPLE)
    find_library( LibArchive NAMES libarchive.dylib )
else()
    find_library( LibArchive NAMES libarchive.so )
endif ()

find_package( ICU REQUIRED COMPONENTS uc i18n )

set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREAD ON)
find_package( Boost REQUIRED COMPONENTS filesystem locale system)


set(CMAKE_CXX_STANDARD 14)

find_package(OpenCL)

include_directories(${Boost_INCLUDE_DIRS} )

add_executable(opencl main.cpp rw_utils.cpp rw_utils.h opencl_utils.cpp opencl_utils.h transitionTable.cpp transitionTable.h)

target_link_libraries(opencl ${OpenCL_Libraries} ${LibArchive} ${Boost_LIBRARIES})