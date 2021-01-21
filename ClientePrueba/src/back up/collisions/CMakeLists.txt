project(Wofenstein3D)

add_library(collisions SHARED
Quadtree.cpp
QuadNode.cpp
Rectangle.cpp
Collidable.cpp
Collectible.cpp
CollectWeapon.cpp
Immovable.cpp
ImmovableWall.cpp
)
