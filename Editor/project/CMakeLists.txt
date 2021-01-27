cmake_minimum_required(VERSION 2.8)

project(edt)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(sdl-lib 
src/Game.cpp 
src/Button.cpp
src/Arrow.cpp 
src/Save.cpp 
src/Textbox.cpp 
src/Settings.cpp
src/Point.cpp
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

find_package(PkgConfig)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)

add_executable (editor src/main.cpp)

target_link_libraries(editor sdl-lib SDL2 SDL2_image SDL2_ttf ${YAMLCPP_LIBRARIES})

install(FILES 
data/arrow.png 
data/brush.png 
data/paint.png 
data/pencil.png 
data/background.png
data/wolfenstein.ttf
data/nivel.yaml
DESTINATION ${CMAKE_BINARY_DIR})
