cmake_minimum_required(VERSION 4.0)
project(geometrylib C)

set(CMAKE_C_STANDARD 11)

add_library(geometrylib STATIC src/geometrylib.c
        src/vec.c
        include/geometrylib_vec.h
        src/plane.c
        include/geometrylib_plane.h)
