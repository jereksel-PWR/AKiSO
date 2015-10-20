cmake_minimum_required(VERSION 2.8.4)
project(Zadanie_1)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

include_directories( ${SDL_INCLUDE_DIRS}  ${SDL_IMAGE_INCLUDE_DIRS})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(SOURCE_FILES_zad1
    ${CMAKE_CURRENT_LIST_DIR}/fade.c)

add_executable(fade ${SOURCE_FILES_zad1})
target_link_libraries(fade ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY})
