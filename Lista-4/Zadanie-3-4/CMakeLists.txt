cmake_minimum_required(VERSION 2.8.4)
project(Zadanie_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

find_package (Threads)

set(SOURCE_FILES_lsh
    ${CMAKE_CURRENT_LIST_DIR}/main.c)

add_executable(lsh ${SOURCE_FILES_lsh})