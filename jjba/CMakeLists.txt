cmake_minimum_required(VERSION 3.12)
project(jjba)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)


set(CMAKE_CXX_STANDARD 14)

add_executable(jjba main.cpp gameName.cpp gameName.h game.cpp game.h object.cpp object.h hitbox.cpp hitbox.h character.cpp character.h standUser.cpp standUser.h jotaro.cpp jotaro.h spritesheet.cpp constants.h level.cpp level.h attack.cpp attack.h)
include_directories(${SDL2_INCLUDE_DIR})
if (WIN32)
    target_link_libraries(jjba ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows)
endif (WIN32)
if (UNIX)
    target_link_libraries(jjba ${SDL2_LIBRARY} -lSDL2main -lSDL2 -lSDL2_image)
endif(UNIX)