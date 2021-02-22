cmake_minimum_required(VERSION 2.8)

project(edt)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_library(sdl-lib 
src/Settings.cpp
src/Tile.cpp
src/Map.cpp
src/Menu.cpp 
src/TextHandler.cpp
src/SDLHandler.cpp
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

find_package(PkgConfig)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)

add_executable (editor src/main.cpp)

target_link_libraries(editor sdl-lib SDL2 SDL2_image SDL2_ttf ${YAMLCPP_LIBRARIES})

file(COPY data/maps DESTINATION ${CMAKE_BINARY_DIR})

install(FILES 
data/tiles.png
data/SelectionMenu.png
data/Save.png
data/Main.png
data/Options.png
data/MainMenuEdit.png
data/splash.png
data/nivel.yaml
data/MainMenu.png
data/MapMenu.png
data/OptionsMenu.png
data/MainCreate.png
data/Players.png
data/beamweapon.ttf
data/config.yaml
DESTINATION ${CMAKE_BINARY_DIR})
