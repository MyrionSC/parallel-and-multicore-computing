cmake_minimum_required(VERSION 3.12)
project(2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_COMPILER mpic++)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(2-seq 4clique-sequential.cpp)
add_executable(2-mp 4clique-mp.cpp)
add_executable(2-mpi 4clique-mpi.cpp)
add_executable(2-hybrid tsp-hybrid.cpp)