cmake_minimum_required(VERSION 2.8.4)
project(Zadanie_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

find_package (Threads)

set(SOURCE_FILES_test1
    ${CMAKE_CURRENT_LIST_DIR}/test1.c)

set(SOURCE_FILES_test3
    ${CMAKE_CURRENT_LIST_DIR}/test3.c)

add_executable(test1 ${SOURCE_FILES_test1})
add_executable(test3 ${SOURCE_FILES_test3})

target_link_libraries (test3 ${CMAKE_THREAD_LIBS_INIT})