cmake_minimum_required(VERSION 2.8.4)
project(Zadanie_5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(SOURCE_FILES_zad5
    ${CMAKE_CURRENT_LIST_DIR}/filozofowie.c)

add_executable(filozofowie ${SOURCE_FILES_zad5})
target_link_libraries (filozofowie pthread)