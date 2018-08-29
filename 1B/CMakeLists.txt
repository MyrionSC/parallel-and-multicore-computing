cmake_minimum_required(VERSION 3.12)
project(1B C)

set(CMAKE_C_STANDARD 99)

add_executable(1B main.c)
add_executable(mandelbrot-sequential mandelbrot-sequential.c)