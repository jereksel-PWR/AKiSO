cmake_minimum_required(VERSION 2.8.4)
project(Zadanie_5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

find_package (Threads)

set(SOURCE_FILES_klient
    ${CMAKE_CURRENT_LIST_DIR}/klient.c
    ${CMAKE_CURRENT_LIST_DIR}/defines.h
    )

set(SOURCE_FILES_serwer
    ${CMAKE_CURRENT_LIST_DIR}/serwer.c
    ${CMAKE_CURRENT_LIST_DIR}/defines.h
    )

add_executable(klient ${SOURCE_FILES_klient})
add_executable(serwer ${SOURCE_FILES_serwer})

target_link_libraries (klient ${CMAKE_THREAD_LIBS_INIT})