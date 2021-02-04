project(Wofenstein3D)

add_library(client_src  SHARED
Player.cpp
SpritesHandler.cpp
SDL_EventHandler.cpp
Hud.cpp
Raycaster.cpp
client.cpp
clientReceiver.cpp
SDLHandler.cpp
Map.cpp
Objects.cpp
Enemies.cpp
client Transmitter.cpp
Walls.cpp
main.cpp
Game.cpp
)

