cmake_minimum_required(VERSION 3.14)
project(genome_substr)

set(CMAKE_CXX_STANDARD 14)

add_executable(genome_substr src/main.cpp src/Bohr.h src/Bohr.cpp)