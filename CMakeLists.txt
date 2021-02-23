cmake_minimum_required(VERSION 2.8)

project(Wofenstein3D)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17")

file(GLOB COMMON_SRC_FILES "Game/src/common_src/*.cpp")
file(GLOB CLIENT_SRC_FILES "Game/src/client_src/*.cpp")
file(GLOB SERVER_SRC_FILES "Game/src/server_src/*.cpp")
file(GLOB COLLISIONS_FILES "Game/src/server_src/collisions/*.cpp")
file(GLOB INVENTORY_FILES "Game/src/client_src/inventory/*.cpp")
file(GLOB ENEMIES_FILES "Game/src/client_src/enemies/*.cpp")
file(GLOB SERVER_INVENTORY_FILES "Game/src/server_src/sp_inventory/*.cpp")

message(${PROJECT_SOURCE_DIR})

add_library(sdl-lib 
Editor/src/Settings.cpp
Editor/src/Tile.cpp
Editor/src/Map.cpp
Editor/src/Menu.cpp 
Editor/src/TextHandler.cpp
Editor/src/SDLHandler.cpp
)

#add_subdirectory(${PROJECT_SOURCE_DIR}src/client_src)
#add_subdirectory(${PROJECT_SOURCE_DIR}src/common_src)
#add_subdirectory(${PROJECT_SOURCE_DIR}src/server_src)

#add_executable (server src/server_src/main.cpp)
#add_executable (client src/client_src/main.cpp)

find_package(PkgConfig)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (server Game/src/server_src/main.cpp ${SERVER_SRC_FILES} ${COMMON_SRC_FILES} ${COLLISIONS_FILES} ${SERVER_INVENTORY_FILES})
add_executable (client Game/src/client_src/main.cpp ${CLIENT_SRC_FILES} ${COMMON_SRC_FILES} ${INVENTORY_FILES} ${ENEMIES_FILES})
add_executable (editor Editor/src/main.cpp)

target_link_libraries(client SDL2 SDL2_image SDL2_ttf SDL2_mixer pthread)
target_link_libraries(server pthread)
target_link_libraries(editor sdl-lib SDL2 SDL2_image SDL2_ttf ${YAMLCPP_LIBRARIES})

install(DIRECTORY
Game/Media
Editor/Media
DESTINATION ${CMAKE_BINARY_DIR})
