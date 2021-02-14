project(Wofenstein3D)

add_library(server_src SHARED
CollisionMap.cpp
updateHandler.cpp
main.cpp
serverPlayer.cpp
protectedMatchEventQueue.cpp
match.cpp
matchHandler.cpp
menuHandler.cpp
server.cpp
serverGame.cpp
serverReceiver.cpp
serverTransmitter.cpp
thAcceptor.cpp
user.cpp
ShootingRaycaster.cpp
matchEventHandler.cpp
bot.cpp
AILua.cpp
)
