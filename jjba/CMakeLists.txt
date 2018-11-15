cmake_minimum_required(VERSION 3.12)
project(jjba)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)


set(CMAKE_CXX_STANDARD 14)

add_executable(jjba main.cpp)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(jjba ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)