cmake_minimum_required(VERSION 3.12)
project(1A C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(1A main.c)


find_package(MPI REQUIRED)

# cmake for floyd-warshall
#cmake_minimum_required(VERSION 3.12)
#project(1A)
#add_executable(1A floyd-warshall.cpp)

