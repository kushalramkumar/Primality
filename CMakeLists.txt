cmake_minimum_required(VERSION 2.8.9)
project (primality)

set (PRIMALITY_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

set(SOURCE_FILES
    primality.c
)

add_executable(primality ${SOURCE_FILES})