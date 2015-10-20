cmake_minimum_required(VERSION 2.8.4)
project(Zadanie_6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

find_package (Threads)

set(SOURCE_FILES_macierz
    ${CMAKE_CURRENT_LIST_DIR}/main.c)

add_executable(macierz ${SOURCE_FILES_macierz})

target_link_libraries (macierz ${CMAKE_THREAD_LIBS_INIT})