cmake_minimum_required(VERSION 2.8)

project(Wofenstein3D)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable (main src/main.cpp)

add_subdirectory(src/collisions)
add_subdirectory(src/inventory)

add_library(sdl-lib 
    src/Game.cpp 
    src/Vector.cpp
    src/Hud.cpp     
    src/Player.cpp 
    src/Raycaster.cpp
    src/Map.cpp 
    src/Walls.cpp 
    src/Objects.cpp 
    src/SDLHandler.cpp
    src/CollisionMap.cpp
    src/SpritesHandler.cpp
)


# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})


target_link_libraries(main sdl-lib SDL2 SDL2_image collisions inventory)

install(FILES 
assets/guns.png 
assets/hud.png 
assets/walls.png 
assets/objects.png 
DESTINATION ${CMAKE_BINARY_DIR})
