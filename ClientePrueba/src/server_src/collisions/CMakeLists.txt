project(Wofenstein3D)

add_library(collisions SHARED
    Quadtree.cpp
    CollectWeapon.cpp
    CollectAmmo.cpp
    CollectHeal.cpp
    CollectKey.cpp
    CollectTreasure.cpp
    Collectible.cpp
    QuadNode.cpp
    Rectangle.cpp
    Collidable.cpp
    Immovable.cpp
    ImmovableWall.cpp
    ImmovableObject.cpp
)
