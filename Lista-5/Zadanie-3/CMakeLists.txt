cmake_minimum_required(VERSION 2.8.4)
project(Zadanie_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(SOURCE_FILES_zad3
    ${CMAKE_CURRENT_LIST_DIR}/main.c
    ${CMAKE_CURRENT_LIST_DIR}/stack.c)

add_executable(b2t ${SOURCE_FILES_zad3})
target_link_libraries (b2t m)