project(Wofenstein3D)

add_library(server_src SHARED
CollisionMap.cpp
main.cpp
match.cpp
matchHandler.cpp
menuHandler.cpp
protectedMatchEventQueue.cpp
server.cpp
serverGame.cpp
serverPlayer.cpp
serverReceiver.cpp
serverTransmitter.cpp
ShootingRaycaster.cpp
thAcceptor.cpp
updateHandler.cpp
user.cpp
userHandler.cpp
)
