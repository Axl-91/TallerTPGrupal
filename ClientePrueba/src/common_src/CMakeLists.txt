project(Wofenstein3D)

add_library(common_src SHARED
socket.cpp
thread.cpp
protectedQueue.cpp
protectedEventQueue.cpp
Vector.cpp
)
