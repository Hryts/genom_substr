cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS -pthread)

find_package( ICU REQUIRED COMPONENTS uc i18n )

set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREAD ON)
find_package( Boost REQUIRED COMPONENTS filesystem locale system)

message(${Boost_VERSION})

include_directories(${Boost_INCLUDE_DIRS} )

add_executable(genome_substr src/main.cpp src/Bohr.h src/Bohr.cpp src/utils.cpp src/utils.h)

target_link_libraries(genome_substr ${Boost_LIBRARIES})