cmake_minimum_required(VERSION 2.8.4)
project(Zadanie_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(SOURCE_FILES_bash
    ${CMAKE_CURRENT_LIST_DIR}/bash.c)

add_executable(bash ${SOURCE_FILES_bash})