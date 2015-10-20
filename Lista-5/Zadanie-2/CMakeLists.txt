cmake_minimum_required(VERSION 2.8.4)
project(Zadanie_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(SOURCE_FILES_zad3
    ${CMAKE_CURRENT_LIST_DIR}/test.c
    ${CMAKE_CURRENT_LIST_DIR}/myfunctions.c)

add_executable(myfunctions ${SOURCE_FILES_zad3})
target_link_libraries (myfunctions m)